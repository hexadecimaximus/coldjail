<p align="center">
  <img src="assets/coldjail-logo.png" width="400"/>
</p>

# Coldjail ❄️🧱 

*Security by default, simplicity by design*

---

**Coldjail** is a process isolation experiment for Linux systems, developed from scratch to explore native Kernel capabilities for creating minimalist sandboxes and containers. 

Unlike complex tools such as Firejail, Coldjail focuses on the direct use of **system calls**, ensuring a small, auditable, and highly educational codebase.

> [!IMPORTANT]
> Coldjail is a **Linux-only** application. It leverages specific kernel primitives (namespaces, `pivot_root`) and is not compatible with BSD, macOS, or Windows.

## 🎯 Project Goals

- **Filesystem Isolation:** Using `pivot_root` within a `mount namespace` to create a root (`/`) completely independent of the host system — overcoming `chroot` limitations.
- **Process & Identity Isolation:** Employment of `PID` and `UTS namespaces` to isolate the process tree and define a custom hostname.
- **Minimalism:** Zero external dependencies (beyond `glibc`), focusing on static binaries like **BusyBox** for the rootfs.
> [!NOTE]
> Busy Box 1.37.0 or highter
- **Low-level Learning:** Manual implementation of virtual mounts (`/proc`, `/sys`, `/tmp`) and direct exploration of the Kernel-Userland interface.

## 🛠️ Architecture & Implementation (v0.1)

Coldjail follows a modular "Pseudo-Object Oriented" approach in C:

- **Process Management:** Secure execution via `fork()` + `waitpid()` to monitor the jailed process.
- **Namespacing:** `unshare()` to decouple `MNT`, `PID`, `NET`, and `UTS` resources.
- **Root Pivoting:** Secure replacement of the root filesystem with automated cleanup of the old mount point (`old_root`).
- **Controlled Environment:** Virtual filesystems mounted with security flags (e.g., `MS_NOSUID`, `MS_NOEXEC` where applicable).



## 🚀 Getting Started (Prototype)

> [!WARNING]
> Current version **requires root privileges** (`sudo`) for namespace manipulation. **Not recommended for production environments.** Use only in VMs or controlled labs.

### Compilation
```bash
make
```

### Usage
```
sudo ./coldjail <path_to_rootfs> [--net=none]
```

### Example with BusyBox

1. Prepare a minimalist rootfs:
```bash
mkdir -p rootfs/{bin,proc,sys,dev,tmp}
cp /bin/busybox rootfs/bin/

Setup symlinks with a following script
Assuming the busybox binary is already in ~/coldjail_root/bin/

for cmd in $(~/coldjail_root/bin/busybox --list); do
    ln -s busybox ~/coldjail_root/bin/$cmd;
done
```

2. Run the jail:
```bash
sudo ./coldjail coldjail_root
```

You will be greeted with: [Coldjail] # — you are now inside the ice wall!


## 📜 License & Inspiration

Coldjail is an original implementation, inspired by the sandboxing concepts of Firejail, Bubblewrap, and nsjail, but without code reuse. Its purpose is academic and technical, 
aiming to deepen the understanding of Linux isolation.
