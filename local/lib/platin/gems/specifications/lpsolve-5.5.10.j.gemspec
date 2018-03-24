# -*- encoding: utf-8 -*-
# stub: lpsolve 5.5.10.j ruby lib
# stub: ext/extconf.rb

Gem::Specification.new do |s|
  s.name = "lpsolve"
  s.version = "5.5.10.j"

  s.required_rubygems_version = Gem::Requirement.new("> 1.3.1") if s.respond_to? :required_rubygems_version=
  s.require_paths = ["lib"]
  s.authors = ["Rocky Bernstein"]
  s.date = "2016-09-14"
  s.description = "A Ruby library for using simplex-method Mixed Integer Linear Programming solver, lpsolve version 0.5.5. \nPick up the C code for lpsolve at http://bashdb.sf.net/lpsolve-5.5.0.10i.tar.bz2\n"
  s.email = "rockby@rubyforge.org"
  s.extensions = ["ext/extconf.rb"]
  s.files = ["ext/extconf.rb"]
  s.homepage = "http://github.org/rocky/rb-lpsolve/"
  s.required_ruby_version = Gem::Requirement.new(">= 1.8.4")
  s.rubyforge_project = "lpsolve"
  s.rubygems_version = "2.5.2.1"
  s.summary = "Ruby interface to lpsolve version 5.5.0.10"

  s.installed_by_version = "2.5.2.1" if s.respond_to? :installed_by_version
end
