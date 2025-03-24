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
- **Comparison**

Let's dive in!

---

# TPM (Trusted Platform Module)

- **What is TPM?**
- **Use cases of TPM**
- **Why TPMs are secure?**
- **TPM alternatives**
- **Modern use**

![bg right h:460](https://m.media-amazon.com/images/I/61tHItzyR9L._AC_SX466_.jpg)


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
- **Modern use**

![bg right h:460](https://upload.wikimedia.org/wikipedia/commons/9/9b/NCipher_nShield_F3_Hardware_Security_Module.jpg)


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

- **Trusted Execution Environment (TEE)** is an **isolated** area in the **CPU** that runs in **parallel** with the main **OS**. 


---

# Use case 1: Mobile Payments

**Problem:** Someone has **stolen** the **phone**, that has **mobile payment** information

**Solution:** We store the **mobile payment** information in the **TEE**, that is **isolated** from the **OS**, thus the attacker cannot access the **mobile payment** information via the **OS**

---

# Use case 2: Biometric authentication

**Problem:** Our laptop with fingerprint authentication has been **stolen**

**Solution:** We store the **fingerprint** information in the **TEE**, that is **isolated** from the **OS**, thus the attacker cannot access the **fingerprint** information via the **OS**

---

# How to use TEE?

| Step | Action |
|------|--------|
| **1** | Normal app requests a secure operation (e.g., encryption, authentication). |
| **2** | The OS sends a request to the TEE via a driver (TEE Client API). |
| **3** | A Secure Monitor Call (SMC) switches execution to the TEE. |
| **4** | The TEE runs the secure code and accesses secure memory or hardware. |
| **5** | The result is securely returned to the normal OS. |

---

# Why TEEs are secure?

**TEEs** are guarantee their **security** by:
- **Isolation** from the **OS**
- **Immutable** **code** and **data**
- **Confidentiality** of the **code** and **data**

--- 

# Modern use:

- **Android** and **iOS** have **TEE** support for **mobile payments**
- **DRM** (Digital Rights Management) uses **TEE** to protect **media content**
- **ARM TrustZone** is a **TEE** implementation for **ARM** processors

---

# SGX (Software Guard Extensions)
Intel's TEE

---

# What is SGX?

- A **TEE** implementation by **Intel** for **x86** processors
- Set of **CPU** instructions that allow **secure** **enclaves** to be created

--- 

# Why do we need TPMs, HSMs, TEEs, or SGX?

- Security by **isolation**
- Guaranteed **tamper resistance**

---

# Comparison

| Feature | TPM | HSM | TEE |
|---------|-----|-----|-----|
| **Primary Function** | Secure boot & system integrity | Key management & encryption | Secure execution of apllications |
| **Hardware integration** | Separate chip | Separate device | CPU |
| **Security level** | High | Very high | Medium |

---

# Comparison

| Feature | TPM | HSM | TEE |
|---------|-----|-----|-----|
| **Performance** | Low | High | Medium |
| **Cost** | Low | High | Medium |
| **Use case** | Secure boot, BitLocker | Payment processing, Digital signatures, Enterprise-level cryptography | Mobile payments, Biometric authentication | 

--- 

# Sources

- [Wikipedia - Trusted Platform Module](https://en.wikipedia.org/wiki/Trusted_Platform_Module)
- [Intel - What is a Trusted Platform Module?](https://www.intel.com/content/www/us/en/business/enterprise-computers/resources/trusted-platform-module.html)
- [Wikipedia - Hardware Security Module](https://en.wikipedia.org/wiki/Hardware_security_module)
- [Wikipedia - Trusted Execution Environment](https://en.wikipedia.org/wiki/Trusted_execution_environment)
- [Wikipedia - Software Guard Extensions](https://en.wikipedia.org/wiki/Software_Guard_Extensions)

## Images
- [https://m.media-amazon.com/images/I/61tHItzyR9L._AC_SX466_.jpg](https://m.media-amazon.com/images/I/61tHItzyR9L._AC_SX466_.jpg)
- [https://upload.wikimedia.org/wikipedia/commons/9/9b/NCipher_nShield_F3_Hardware_Security_Module.jpg](https://upload.wikimedia.org/wikipedia/commons/9/9b/NCipher_nShield_F3_Hardware_Security_Module.jpg)
