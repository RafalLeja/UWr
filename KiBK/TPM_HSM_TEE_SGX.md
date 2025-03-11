---
marp: true
title: Introduction to TPM, HSM, TEE, and SGX
theme: gradient
paginate: true
---

# Introduction to TPM, HSM, TEE, and SGX

Agenda:

- **TPM (Trusted Platform Module)**
- **HSM (Hardware Security Module)**
- **TEE (Trusted Execution Environment)**
- **SGX (Software Guard Extensions)**

Let's dive in!

---

# TPM (Trusted Platform Module)

- **What is TPM?**
- **Use cases of TPM**
- **Why TPMs are secure?**
- **TPM alternatives**
- **Do we need TPM?**

---

# What is TPM?

- **Trusted Platform Module (TPM)** is a secure crypto-processor that implements the ISO/IEC 11889 standard.
- **TPMs** provide:
  - **Hardware random number generator**
  - **Secure key genration and storage**
  - **Remote attestation** (hash key summary of the hardware and software configuration)
  - **Binding** (encrypting data with a key that can only be decrypted by the TPM)
  - **Sealed storage** (encrypting data with a key based on system configuration)
  
---

# Use case 1: UEFI Secure Boot

**Problem:** Someone has **tampered** with the **boot loader**

**Solution:** **UEFI Secure Boot** verifies the **boot loader**,
by checking the **signature** of the **boot loader** with the **public key** stored in the **TPM**

---

# Use case 2: BitLocker

**Problem:** Someone has **stolen** the **hard drive**

**Solution:** **BitLocker** encrypts the **hard drive** with a **key** stored in the **TPM**

---

# Why TPMs are secure?

**TPMs** are guarantee their **security** by:
- **Isolation:** TPM is a **separate chip** from the **CPU**
- **Tamper resistance:** TPM is **hard to tamper** with
- **Burned-in keys:** TPM has **keys** that are **burned-in** during manufacturing, thus **cannot be extracted**
- **Protection against targeted attacks:** TPMs are **designed** to **resist** **Brute-force** attacks, locking out after a certain number of attempts

---

# Alternatives to TPM

- **fTPM:** **TPM** implemented in **firmware** (e.g. **AMD PSP**)
- **Software TPM:** **TPM** implemented in **software** (e.g. **Intel PTT**)
- **Virtual TPM:** **TPM** implemented in **software** (e.g. **QEMU**)

---

# Do we need TPM?

**Yes**, storing and generating **keys** on a software level is vunerable to **attacks**. **TPMs** provide a **secure** way to store and generate **keys**.

---

# Modern use:
- **Windows 11** requires a **TPM 2.0** chip.
- Most modern **CPUs** have a integrated **TPM** chip.
- 20$ **TPM** for a motherboard-->


![bg right h:460](https://m.media-amazon.com/images/I/61tHItzyR9L._AC_SX466_.jpg)

---

# HSM (Hardware Security Module)
TPM's big brother

- **What is HSM?**
- **Use cases of HSM**
- **Why HSMs are secure?**
- **HSM alternatives**
- **Do we need HSM?**


---

# What is HSM?

- **Hardware Security Module (HSM)** is a secure crypto-processor that implements the FIPS 140-2 standard.
- **HSMs**
  - **Store** and **manage** **keys**
  - **Encrypt** and **decrypt** data (up to 1000s of 1024-bit RSA operations per second)
  - **Sign** data
  - **Generate** random numbers
  - **Secure** **remote** **access**

---

# Use case 1: Payment processing

**Problem:** Someone has paid with a **credit card**, we need to **verify** the **payment**

**Solution:** **HSM** **decrypts** the **payment** **information** with the **key** stored in the **HSM**, and **verifies** the **payment**

---

# Use case 2: Digital signatures

**Problem:** We hava a **HTTPS** website, we need to **encrypt** the **data**

**Solution:** **HSM** **encrypts** the **data** with the **key** stored in the **HSM**, offloading the **CPU**

---

# Why HSMs are secure?

**HSMs** are guarantee their **security** by:
- **Isolation:** HSM is a **separate device** from the **CPU**
- **Tamper resistance:** HSM is **hard to tamper** with

---

# Alternatives to HSM

- **KMS** (Key Management Service): **HSMs** as a **service**

---

# Modern use:
- **Cloud HSMs** (e.g. **Google Cloud HSM**)
- **PCI HSMs** (e.g. **YubiHSM**) ~5000$ --> 

![bg right h:460](https://upload.wikimedia.org/wikipedia/commons/9/9b/NCipher_nShield_F3_Hardware_Security_Module.jpg)

---

# TEE (Trusted Execution Environment)

- **What is TEE?**
- **Use cases of TEE**
- **Why TEEs are secure?**
- **TEE alternatives**
- **Do we need TEE?**
- **Modern use**

---

# What is TEE?

- **Trusted Execution Environment (TEE)** is a secure **execution environment** is **isolated** from the **OS**