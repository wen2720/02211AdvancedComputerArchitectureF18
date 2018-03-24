/*
   Copyright 2013 Technical University of Denmark, DTU Compute.
   All rights reserved.

   This file is part of the time-predictable VLIW processor Patmos.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

      1. Redistributions of source code must retain the above copyright notice,
         this list of conditions and the following disclaimer.

      2. Redistributions in binary form must reproduce the above copyright
         notice, this list of conditions and the following disclaimer in the
         documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER ``AS IS'' AND ANY EXPRESS
   OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
   NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   The views and conclusions contained in the software and documentation are
   those of the authors and should not be interpreted as representing official
   policies, either expressed or implied, of the copyright holder.
 */

/*
 * Definition of Argo network types
 *
 * Authors: Rasmus Bo Soerensen (rasmus@rbscloud.dk)
 *
 */

package argo

import Chisel._
import Node._

class ArgoLink(linkWidth : Int) extends Bundle() {
  val startOfPacket = Bits(width = 1)
  val endOfPacket = Bits(width = 1)
  val valid = Bits(width = 1)
  val data = Bits(width = linkWidth)

  // This does not really clone, but Data.clone doesn't either
  override def clone() = {
    val res = new ArgoLink(linkWidth)
    res.asInstanceOf[this.type]
  }
}

class SelLink(linkWidth : Int) extends ArgoLink(linkWidth) {
  val sel = Bits(width = 4)

  // This does not really clone, but Data.clone doesn't either
  override def clone() = {
    val res = new SelLink(linkWidth)
    res.asInstanceOf[this.type]
  }
}

class RouterPort(linkWidth : Int) extends Bundle() {
  val out = new ArgoLink(linkWidth).asOutput
  val in = new ArgoLink(linkWidth).asInput

  // This does not really clone, but Data.clone doesn't either
  override def clone() = {
    val res = new RouterPort(linkWidth)
    res.asInstanceOf[this.type]
  }
}

class IRQ() extends Bundle() {
  val remote = Bits(width = 1)
  val incomming = Bits(width = 1)
}

class SPMMasterSignals(linkWidth : Int, addrWidth: Int) extends Bundle() {
  val address = Bits(width = addrWidth)
  val wrEn = Bits(width = 1)
  val writeData = Bits(width = linkWidth * 2)
  

  // This does not really clone, but Data.clone doesn't either
  override def clone() = {
    val res = new SPMMasterSignals(linkWidth, addrWidth)
    res.asInstanceOf[this.type]
  }
}

class SPMSlaveSignals(linkWidth : Int) extends Bundle() {
  val readData = Bits(width = linkWidth * 2)

  // This does not really clone, but Data.clone doesn't either
  override def clone() = {
    val res = new SPMSlaveSignals(linkWidth)
    res.asInstanceOf[this.type]
  }
}

class SPMMasterPort(linkWidth : Int, addrWidth: Int) extends Bundle() {
  val master = new SPMMasterSignals(linkWidth, addrWidth).asOutput
  val slave = new SPMSlaveSignals(linkWidth).asInput
}

class SPMSlavePort(linkWidth : Int, addrWidth: Int) extends Bundle() {
  val master = new SPMMasterSignals(linkWidth, addrWidth).asInput
  val slave = new SPMSlaveSignals(linkWidth).asOutput
}