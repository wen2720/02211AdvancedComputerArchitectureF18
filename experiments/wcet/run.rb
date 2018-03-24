#!/usr/bin/env ruby
#
# Experiments with compiler integration
#

# stdlib
require 'yaml'
require 'set'
require 'fileutils'

# load libraries
begin
  require 'lib/experiments'
rescue LoadError => e
  $:.unshift File.join(File.dirname(__FILE__),"..")
  require 'lib/experiments'
end
require_configuration 'wcet'


# configuration
config = default_configuration()
config.build_log     = File.join(config.builddir, 'build.log')
config.report        = File.join(config.workdir, 'report.yml')
config.do_update        = false
config.keep_trace_files = true

# customized benchmark script
class BenchTool < WcetTool
  def initialize(pml, options)
    super(pml,options)
  end
  def BenchTool.run(options, console_opts)
    redirect_output(console_opts) do
      pml = BenchTool.new(PMLDoc.from_files(options.input), options).run_in_outdir
      pml.dump_to_file(options.output) if options.output
    end
  end
  def BenchTool.import_ff(benchmark, options)
    return [] if options.use_trace_facts
    ff = benchmark['name'] + '.ff.pml'
    if not File.exist?(ff)
      return []
    end
    [ff]
  end
end


# remove old files unless updating
FileUtils.remove_entry_secure(config.build_log) if File.exist?(config.build_log) && ! config.do_update

# options
config.options = default_options(:nice_pasim => config.nice_pasim)
config.options.enable_sweet = false
config.options.enable_wca   = true
config.options.runcheck     = false # true
config.options.trace_analysis = false
config.options.use_trace_facts = false
# config.options.compute_criticalities = true
config.options.disable_ait = true
config.options.compare_trace_facts = true

# run benchmarks
build_and_run(config, BenchTool)

# summarize
keys = %w{benchmark build analysis source analysis-entry cycles}
print_csv(config.report, :keys => keys, :outfile => File.join(config.workdir,'report.csv'))
print_table(config.report, keys)


