---
format: pml-0.1
triple: patmos-unknown-unknown-elf
machine-configuration:
  memories:
    - name: "main"
      size: 0x200000
      transfer-size: 8
      read-latency: 0
      read-transfer-time: 0
      write-latency: 0
      write-transfer-time: 0
    - name: "local"
      size: 2048
      transfer-size: 4
      read-latency: 0
      read-transfer-time: 0
      write-latency: 0
      write-transfer-time: 0
  caches:
    - name: "data-cache"
      block-size: 8
      associativity: 1
      size: 2048
      policy: "lru"
      type: "set-associative"
    - name: "method-cache"
      block-size: 512
      associativity: 8
      size: 4096
      policy: "fifo"
      type: "method-cache"
    - name: "stack-cache"
      block-size: 4
      size: 1024
      type: "stack-cache"
  memory-areas:
    - name: "code"
      type: "code"
      memory: "main"
      cache: "method-cache"
      address-range:
        min: 0
        max: 0xFFFFFFFF
    - name: "data"
      type: "data"
      memory: "main"
      cache: "data-cache"
      address-range:
        min: 0
        max: 0xFFFFFFFF
      attributes:
        - key: "heap-end"
          value: 0x100000
        - key: "stack-base"
          value: 0x200000
        - key: "shadow-stack-base"
          value: 0x1f8000
tool-configurations:
  - name: "clang"
    options: ["-mpatmos-disable-vliw"]                  
