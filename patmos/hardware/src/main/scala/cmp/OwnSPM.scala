/*
 * A pool of shared scratchpad memories with owners.
 * 
 * Super simple solution without any ownership enforcement,
 * just merge all requests with an OR and have the response
 * routed to all.
 * Ownership and transfer has to be organized in software
 * (e.g., use a shared variable in main memory).
 *
 * Author: Martin Schoeberl (martin@jopdesign.com)
 */

package cmp

import Chisel._

import patmos._
import patmos.Constants._
import ocp._

class OwnSPM(nrCores: Int, nrSPMs: Int, size: Int) extends Module {

  val io = Vec(nrCores, new OcpCoreSlavePort(ADDR_WIDTH, DATA_WIDTH))

  val bits = log2Up(nrSPMs)
  println("OwnSPM: cnt = "+nrSPMs+" bits = "+bits)
  
  val masters = Vec(nrSPMs, Vec(nrCores, new OcpCoreSlavePort(ADDR_WIDTH, DATA_WIDTH)))
  val spms = (0 until nrSPMs).map(i => Module(new Spm(size)))

  for (s <- 0 until nrSPMs) {
    // And gate non-active masters.
    for (i <- 0 until nrCores) {
      masters(s)(i).M.Addr := UInt(0)
      masters(s)(i).M.Data := UInt(0)
      masters(s)(i).M.Cmd := UInt(0)
      masters(s)(i).M.ByteEn := UInt(0)
      when(io(i).M.Cmd =/= OcpCmd.IDLE && io(i).M.Addr(16+bits-1, 16) === UInt(s)) {
        masters(s)(i).M := io(i).M
      }
    }

    // Or the master signals
    spms(s).io.M.Addr := masters(s).map(_.M.Addr).reduce((x, y) => x | y)
    spms(s).io.M.Data := masters(s).map(_.M.Data).reduce((x, y) => x | y)
    spms(s).io.M.Cmd := masters(s).map(_.M.Cmd).reduce((x, y) => x | y)
    spms(s).io.M.ByteEn := masters(s).map(_.M.ByteEn).reduce((x, y) => x | y)
  }

  // Connect SPM out to output muxes and muxes to slave responses
  for (i <- 0 until nrCores) {
    val mux = Vec(nrSPMs, new OcpCoreSlavePort(ADDR_WIDTH, DATA_WIDTH))
    for (j <- 0 until nrSPMs) {
      mux(j).S := spms(j).io.S
    }
    io(i).S := mux(RegNext(io(i).M.Addr(16+bits-1, 16))).S
  }
}

/**
  * A simple, single SPM with ownership.
  * Still useful?
  */
class OwnSPMSingle(nrCores: Int, size: Int) extends Module {

  val io = Vec(nrCores, new OcpCoreSlavePort(ADDR_WIDTH, DATA_WIDTH))

  val masters = Vec(nrCores, new OcpCoreSlavePort(ADDR_WIDTH, DATA_WIDTH))

  // And gate non-active masters.
  // How to have a more elegant solution with a single assignment?
  for (i <- 0 until nrCores) {
    masters(i).M.Addr := UInt(0)
    masters(i).M.Data := UInt(0)
    masters(i).M.Cmd := UInt(0)
    masters(i).M.ByteEn := UInt(0)
    when(io(i).M.Cmd =/= OcpCmd.IDLE) {
      masters(i).M := io(i).M
    }
  }

  val spm = Module(new Spm(size))

  // Or the master signals
  spm.io.M.Addr := masters.map(_.M.Addr).reduce((x, y) => x | y)
  spm.io.M.Data := masters.map(_.M.Data).reduce((x, y) => x | y)
  spm.io.M.Cmd := masters.map(_.M.Cmd).reduce((x, y) => x | y)
  spm.io.M.ByteEn := masters.map(_.M.ByteEn).reduce((x, y) => x | y)
  // have all cores connected to the slave response
  for (i <- 0 until nrCores) {
    io(i).S <> spm.io.S
  }
}