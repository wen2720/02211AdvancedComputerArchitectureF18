---
format:          pml-0.1
triple:          patmos-unknown-unknown-elf
flowfacts:
  - scope:
      function: main
    lhs:
      - factor: -99
        program-point:
          marker : 0
      - factor: 1
        program-point:
          marker : 1
    op: less-equal
    rhs: 0
    level: bitcode
    origin: user.bc
  - scope:
      function: main
    lhs:
      - factor: -99
        program-point:
          marker : 1
      - factor: 1
        program-point:
          marker : 2
    op: less-equal
    rhs: 0
    level: bitcode
    origin: user.bc
