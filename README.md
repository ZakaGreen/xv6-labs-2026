# xv6 — learning what happens underneath

My operating-systems lab work at **FEI STU**, based on the **xv6 RISC-V teaching operating system**.

Pointers and structures in C became much easier for me to understand once I studied how memory works. These labs let me explore related ideas inside a small operating system: processes, system calls, page tables and traps.

The coursework is maintained on [GitLab](https://gitlab.com/ilushkalubotin/xv6-xliubotin-2026). This GitHub copy brings it together with my other programming work and preserves the existing branch history.

## Find a lab

Each branch is a separate lab snapshot. This table describes the work present in the imported history, not a claim that every lab or test is complete.

| Branch | Area |
| --- | --- |
| [util](https://github.com/ZakaGreen/xv6-labs-2026/tree/util) | User-space utilities, processes and pipes. |
| [syscall](https://github.com/ZakaGreen/xv6-labs-2026/tree/syscall) | System-call exercises, including interposition and sandbox-related tasks. |
| [pgtbl](https://github.com/ZakaGreen/xv6-labs-2026/tree/pgtbl) | Page-table and process-memory exercises. |
| [traps](https://github.com/ZakaGreen/xv6-labs-2026/tree/traps) | Kernel backtraces, `sigalarm` and `sigreturn`. |
| [lock](https://github.com/ZakaGreen/xv6-labs-2026/tree/lock) | Locking lab, started and still in progress. |

The `main` branch adds this guide to the `util` snapshot. The five lab branches retain their original commits. This is a copy of the GitLab state at publication, not an automatically synchronised mirror.

## Explore locally

```bash
git clone https://github.com/ZakaGreen/xv6-labs-2026.git
cd xv6-labs-2026
git switch util
make qemu
```

Building requires a suitable RISC-V toolchain and QEMU with RISC-V support. See the original [upstream README](README) for the toolchain references. Follow the relevant assignment when selecting a lab branch or running its checks. Lab builds and grading were not rerun as part of this portfolio import.

## Where the code comes from

xv6 itself is the work of its upstream authors at MIT and its contributors. My contribution is the coursework recorded in the student commits; I did not write the operating system from scratch and this repository does not represent enrolment at MIT.

The original [LICENSE](LICENSE), upstream README and history are preserved. The GitLab repository remains the coursework source.

[Back to my profile](https://github.com/ZakaGreen)
