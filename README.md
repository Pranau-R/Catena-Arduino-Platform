# The MCCI Catena Arduino Platform Library

This library provides a simple-to-use framework for taking advantage of many of the features of the MCCI Catena&reg; Arduino products.

_Apologies_: This document is a work in progress, and is published in this intermediate form in hopes that it will still be better than nothing.

[![GitHub release](https://img.shields.io/github/release/mcci-catena/Catena-Arduino-Platform.svg)](https://github.com/mcci-catena/Catena-Arduino-Platform/releases/latest) [![GitHub commits](https://img.shields.io/github/commits-since/mcci-catena/Catena-Arduino-Platform/latest.svg)](https://github.com/mcci-catena/Catena-Arduino-Platform/compare/v0.14.0...master) [![Build Status](https://travis-ci.com/mcci-catena/Catena-Arduino-Platform.svg?branch=master)](https://travis-ci.com/mcci-catena/Catena-Arduino-Platform)

<!-- TOC depthFrom:2 updateOnSave:true -->

- [Overview](#overview)
- [Coding Practices](#coding-practices)
- [Components](#components)
	- [Namespace `McciCatena`](#namespace-mccicatena)
	- [Class `Catena` and header file `Catena.h`](#class-catena-and-header-file-catenah)
	- [Board-specific Classes](#board-specific-classes)
	- [Class derivation](#class-derivation)
	- [Platform Management](#platform-management)
	- [Pollable Interface](#pollable-interface)
	- [LoRaWAN Support](#lorawan-support)
	- [FRAM Storage Management](#fram-storage-management)
		- [FRAM Storage Formats](#fram-storage-formats)
			- [Object Storage Structure](#object-storage-structure)
			- [Bit layout of `uSizeKey`](#bit-layout-of-usizekey)
			- [The FRAM header object](#the-fram-header-object)
		- [Adding FRAM objects](#adding-fram-objects)
		- [Class hierarchy within the FRAM library](#class-hierarchy-within-the-fram-library)
	- [Asynchronous Serial Port Command Processing](#asynchronous-serial-port-command-processing)
		- [Collecting lines asynchronously from streams](#collecting-lines-asynchronously-from-streams)
		- [The command parser](#the-command-parser)
	- [`Catena_functional.h`](#catena_functionalh)
- [Command Summary](#command-summary)
	- [Standard commands](#standard-commands)
	- [FRAM commands](#fram-commands)
	- [LoRaWAN commands](#lorawan-commands)
		- [LoRaWAN Parameters](#lorawan-parameters)
- [Example sketches](#example-sketches)
	- [`catena_hello`](#catena_hello)
	- [`catena_hello_lora`](#catena_hello_lora)
	- [`catena_usercommand`](#catena_usercommand)
- [Board Support Dependencies](#board-support-dependencies)
- [Other Libraries and Versions Required](#other-libraries-and-versions-required)
- [Library Release History](#library-release-history)

<!-- /TOC -->
<!-- Due to a bug in Markdown TOC, the table is formatted incorrectly if tab indentation is set other than 4. Due to another bug, this comment must be *after* the TOC entry. -->

## Overview

## Coding Practices

In order to assist people who are not everyday readers and writer of C++, this library adopts some rules.

1. All names are in the `McciCatena` namespace.

2. In classes with elaborate hierarchy, we normally define a private synonym of `Super` which refers to the parent class. This is done so that we can change parent/child relationships without breaking code.

3. We tend to use the `m_...` prefix on the names of class member fields.

4. We tend to use `this->m_...` to refer to class members (rather than omitting `this->`). We do this for emphasis, and to avoid visual ambituity.

5. We tend to name classes starting with a lower-case letter `c`, i.e., <code><strong>c</strong><em><u>ClassName</u></em></code>. For the `Catena...` classes, we don't follow this rule, however.

6. We don't use most of the standard C++ library (because of the frequent use of exceptions), nor do we use exceptions in our own code. The exception framework tends to be inefficient, and it's a source of coding problems because the error paths are not directly visible.

7. However, we do take advantage of some of the C++-11 header files, such as `<functional>`, `<type_traits>`, and `<cstdint>`.  (Sometimes we have to do extra work for this.)

## Components

### Namespace `McciCatena`

Unless otherwise specified, all symbols are defined inside namespace `McciCatena`. Usually sketches begin with something like this:

```c++
#include <Catena.h>

//... other includes

using namespace McciCatena;
```

### Class `Catena` and header file `Catena.h`

`Catena.h` is the main header file for the library. It uses the `#defines` injected by `board.txt` and `platform.txt` from the Arduino environment to create a class named `Catena` derived from the `Catena...` class that is specific to the board for which the software is being built. This allows examples to be source-compatible, no matter which Catena is our target.

### Board-specific Classes

`Catena.h` defines the class `Catena` in terms on one of the following classes based on the setting of the BSP:

The known classes and header files are:

Class                 | Header File             | Description
----------------------|-------------------------|------------------
`Catena4410`          | `Catena4410.h`          | First generation MCCI systems with BME180
`Catena4420`          | `Catena4420.h`          | Feather M0 Bluetooth + LoRa Radio Wing
`Catena4450`          | `Catena4450.h`          | MCCI Catena 4450
`Catena4460`          | `Catena4460.h`          | MCCI Catena 4460
`Catena4470`          | `Catena4470.h`          | MCCI Catena 4470
`Catena4551`          | `Catena4551.h`          | MCCI Catena 4551 first-generation Murata-based board.
`Catena4610`          | `Catena4610.h`          | MCCI Catena 4610 second-generation Murata-based board with LiPo charging
`Catena4611`          | `Catena4611.h`          | MCCI Catena 4611 second-generation Murata-based board with fixed Vdd, no charging
`Catena4612`          | `Catena4612.h`          | MCCI Catena 4612 second-generation Murata-based board with variable Vdd, no charging.
`Catena4801`          | `Catena4801.h`          | MCCI Catena 4801 Murata-based board with Modbus.

### Class derivation

The following figures gives the class derivation hierarchy for the board classes.  The first figure just gives relationships; the second has details about the members of each class.

<!-- see assets/CatenaBase.plantuml. for some bizarre reason github won't render these unless image links are http (not https). insert "hide members" before @enduml for the condensed "relationships" drawing. -->
**Catena Class Relationshiops:**

[![**Catena Class Relationships**:](http://www.plantuml.com/plantuml/png/xLXRRzis57xNho0QOBNT1hNTsWkQFLHnBXDcEuRjh0z58L3IiQD54ZsICffb-U-ZBg8enbATh1rGB6yYl-_Spo5fVs0SKnw70NenmXmYZ4O1PWpzwWF5rBs-VM6yUObc0OxurMIC_12l0Qq8HJdRJTdN6VlMUFd6Y708R8DTG1FNzNFQdM5WXt6ANPwBPC09PY10X5u9C1RWsPKrV6SxyMe5rER73n2nyADrZa0KX-XoTZOtbzRqmZuVcnUB4fYDpUNvvNoYxD-9QBdltiT-nD_sRPu4naKquNc0ryo-03uXtZGE7Q2jTaN28IH0BeaOXoyRMfLxPLjCo7dWvK9RudjeWLSmeyBGAjzDfVCmJl80KKVONDmoiLiOBF9qZr8r3gpzgAB1lSOKTV84Jd48hNRccM8x0DYepcn84AXhAhIAKEYbymUuF4Umvur86EB8OrhqIh4wctAHS0ug-gho1zLgej3EGaqnToPy4hKyYqI0831rlSue2qu1XrOazc4aOE4heO8glpDQRZLZ2xYoFZRkQvflWKEltwkqtrNa_nc3TIfz_lJvU0Sisr30Mj7IHb6Bfcp8jYDReDJtO8BPZMJTwAnu502c2USrAZSNmALOtX4ZStasDUsYuTEcaXrAg7NQodWFedkjpLj7xy5lhLy9fAEqez1NoBPq9PAPzRr2pOhGqeiY1FPDJbuYwPE0BZT0CHTwqj7M2OgiWX-K2MkQ1dS1rCV17B1tAxfKMINmOJ5ikTkpAn6IFCCcvWnjHvlOyfQay21hFasE-N-1S3JIoIbLnX7QrJXJj2PVeRsfACc6PxuS2IrpxZRC5m_VzlSRh-VnUXwlv_6g7wLpmFmQwAIBxkJxnfoQuyiBUsPDbKVFgNLXBSrnkRiA2EOeISFl3kRgK-50xqEJUY82Oe_977yqf-_VpoZP-imdaOZ3YbOaAwwssKfgqdwymYLs0aWrvl0DtB9CcUBZDqbQOW3TrUIeJlfZKZoAm_vD9be6fvv1k-PP3gN-nDFfNntyJC3DtUYiWIUVsMxgXTWv8OIFI1pnrazEyTbkU9Zj6AXrQJQjIaewBCoARaw-j0QNPfFzL0l3MoWdl_bM6DSqyiuQDMV_lqXdqo1fKCmaLFLEUPZBD39mMLjULqtFwJrdGTRjQA-wLIeovsvne-l7dcwqrK7P_hQmp3vzRZSTbv9t_DX-UJSOV6cQG2LzjIg6lN-jugZx21KLoNUzRktXKz6d_hnx-EjEMlXEHwsitDuArpS5Qlyc5Ew8lF-_ZNoGHzuSMJRnFkKn3b3DKVnzf_6XvyCVrlEVVrJF1uFUVfxhWiDUzwc2JxROVvhWKNT_YyhVJR_yVNXO-Rj61zLNXM6eJ1MMJq53M-ia-Lwi8Sg3pTWXK-NqcZZQ4zFGDwgg1jsl48PDX6ms34F9L0dAwz-eh2GXlu4Rq66l2HNtfc6KUZIzFQDKeYdjraCDKdsZjAlvqHEjTUrxW4887Q3C-02H5uV1Fm00)](https://www.plantuml.com/plantuml/svg/xLXRRzis57xNho0QOBNT1hNTsWkQFLHnBXDcEuRjh0z58L3IiQD54ZsICffb-U-ZBg8enbATh1rGB6yYl-_Spo5fVs0SKnw70NenmXmYZ4O1PWpzwWF5rBs-VM6yUObc0OxurMIC_12l0Qq8HJdRJTdN6VlMUFd6Y708R8DTG1FNzNFQdM5WXt6ANPwBPC09PY10X5u9C1RWsPKrV6SxyMe5rER73n2nyADrZa0KX-XoTZOtbzRqmZuVcnUB4fYDpUNvvNoYxD-9QBdltiT-nD_sRPu4naKquNc0ryo-03uXtZGE7Q2jTaN28IH0BeaOXoyRMfLxPLjCo7dWvK9RudjeWLSmeyBGAjzDfVCmJl80KKVONDmoiLiOBF9qZr8r3gpzgAB1lSOKTV84Jd48hNRccM8x0DYepcn84AXhAhIAKEYbymUuF4Umvur86EB8OrhqIh4wctAHS0ug-gho1zLgej3EGaqnToPy4hKyYqI0831rlSue2qu1XrOazc4aOE4heO8glpDQRZLZ2xYoFZRkQvflWKEltwkqtrNa_nc3TIfz_lJvU0Sisr30Mj7IHb6Bfcp8jYDReDJtO8BPZMJTwAnu502c2USrAZSNmALOtX4ZStasDUsYuTEcaXrAg7NQodWFedkjpLj7xy5lhLy9fAEqez1NoBPq9PAPzRr2pOhGqeiY1FPDJbuYwPE0BZT0CHTwqj7M2OgiWX-K2MkQ1dS1rCV17B1tAxfKMINmOJ5ikTkpAn6IFCCcvWnjHvlOyfQay21hFasE-N-1S3JIoIbLnX7QrJXJj2PVeRsfACc6PxuS2IrpxZRC5m_VzlSRh-VnUXwlv_6g7wLpmFmQwAIBxkJxnfoQuyiBUsPDbKVFgNLXBSrnkRiA2EOeISFl3kRgK-50xqEJUY82Oe_977yqf-_VpoZP-imdaOZ3YbOaAwwssKfgqdwymYLs0aWrvl0DtB9CcUBZDqbQOW3TrUIeJlfZKZoAm_vD9be6fvv1k-PP3gN-nDFfNntyJC3DtUYiWIUVsMxgXTWv8OIFI1pnrazEyTbkU9Zj6AXrQJQjIaewBCoARaw-j0QNPfFzL0l3MoWdl_bM6DSqyiuQDMV_lqXdqo1fKCmaLFLEUPZBD39mMLjULqtFwJrdGTRjQA-wLIeovsvne-l7dcwqrK7P_hQmp3vzRZSTbv9t_DX-UJSOV6cQG2LzjIg6lN-jugZx21KLoNUzRktXKz6d_hnx-EjEMlXEHwsitDuArpS5Qlyc5Ew8lF-_ZNoGHzuSMJRnFkKn3b3DKVnzf_6XvyCVrlEVVrJF1uFUVfxhWiDUzwc2JxROVvhWKNT_YyhVJR_yVNXO-Rj61zLNXM6eJ1MMJq53M-ia-Lwi8Sg3pTWXK-NqcZZQ4zFGDwgg1jsl48PDX6ms34F9L0dAwz-eh2GXlu4Rq66l2HNtfc6KUZIzFQDKeYdjraCDKdsZjAlvqHEjTUrxW4887Q3C-02H5uV1Fm00 "SVG image of Class Relationships")

**Catena Class Hierarchy (full detail):**
<!-- see assets/CatenaBase.plantuml, and comment above about http/https -->
[![**Catena Class Hierarchy:**](http://www.plantuml.com/plantuml/png/xLXRSzeu57xthz0qCrkWpHHeePbc7-gGXFKi5mR8zg7JyGXR42-snKeoKpQR_xwovOkaO4EopKDdysQTxpkNetEE9FXC6IGi2dpmgWSP2Y7e-P1Iy9k722JExUwLyUurcFWmP3V30V02k49WYGb8sKx2lXNidV7wdH720D4DT10OEewNqkuC0oue8z1XgOe0BY1570JW3GSZ3bxTMDqFzY9QBX6nsVa3X2-yS9KYA8m2C9vSJSsvDUhRrmEpFok0oS2SNu-dGqb-nxDbddCVUI5xtxPPd1ZZsGJNFbnHku_O4BkZA5WWKgih6WkCVU3Wa3BqVKDKlJUsHRcUYznKQOiz5ypW4aq8TxHCfObsciP5cY1eS9-p7UNIp66sJ_SWCRD0AozKB3Yta816ke4Z6A1QNKGc-VOHsiZ1RB3losl2hV9Ko7Zn9t9OYa3NxU4WWA5BjUobOZKsnIBcd2ZsLFqJjPeWi4Mg2UPCU4oybbSXJn1nJ5wl16N628A15N8vwd6Onue9f-RVWfPw5MmEA-jpuxwa-MOmSDijfVrkGk-l25cNUSnVlvtlWqKR2bWjMj8eSj4aGTvsU8i8yLmqX7ITizOwA-hv29AOynOKmXbYgLhU4JrpVZKoxQpXawRAEnGJwx8cU0-oUwlDMqFlmHzjNqga8RKZjvVfrdGZELFqlKGLHQZfHSaL3WUVbYYFYKFZ3IAGSJl9QEi4ILV2JueDgve6PuQ81_qfWkwETwcqYk7JRDZIi2StFANy31kQ4x3jRIBBdUCi0j5ycXxr_aOyq50d9zGyZy1MyqpGalqAx8rYH0pFTDxZLgRCgPWl5hnllupNotYzZDTnurK-IjS8ibj4Xarmbxzlp94v6FVjYJMI7ZsNLj-QcuD2klGnP23UXZyMaCbFXHEz3qtYyWomFS1J-CKSVVeq8NZhKG-7F0yhN69HN4rOYsjIVxp1ELpuAB6OmckqeyAO5ECFsRJO0RWhsQCoxIznyGWCsckXMYGddq7xvbaPIlM9fz8F3hvGSD8m6Yl4uayXJQBWaWkCMGz78QlziiW-wnKFipq3jIhS9bL9IAUPMzxDyPVMuBdRM9vOeN2BYicllXK69OsyjqQ7T_-vjxDoa5GeeZcaHYSzpFDjfCYXzVowgdfE7piBMTtEZggRKf4fSx8RNJ_sTAUr1X3oRUQPVlrMhpekSzxvO_lbGwVplMe2fUqhDT5j_MSJPyr7c50qFxIQfOUFOa_-UVVmrrtkuPcEshnoHnjShJFK_fqRt9Dv-t-RUIVDl3epCV4UOH7qGSbH_CpJ-23oxayR-SUVDV9EftLSvBfYjzLygkAJFRQVfdZMFDwZz7VJh_-SdYf_r-YW_AhWcX8pXTMdeA6jzvBYsQuW9WURiKT7vRGgEUeJqz05ggbEym2XUuZmiMaOqau9KBd-3MMbQFCRk0BjjgfGVcyQHc57izio2YEQqMOvLA7LDWg_MXmjtbgVKUX6WVyl)](https://www.plantuml.com/plantuml/png/xLXRSzeu57xthz0qCrkWpHHeePbc7-gGXFKi5mR8zg7JyGXR42-snKeoKpQR_xwovOkaO4EopKDdysQTxpkNetEE9FXC6IGi2dpmgWSP2Y7e-P1Iy9k722JExUwLyUurcFWmP3V30V02k49WYGb8sKx2lXNidV7wdH720D4DT10OEewNqkuC0oue8z1XgOe0BY1570JW3GSZ3bxTMDqFzY9QBX6nsVa3X2-yS9KYA8m2C9vSJSsvDUhRrmEpFok0oS2SNu-dGqb-nxDbddCVUI5xtxPPd1ZZsGJNFbnHku_O4BkZA5WWKgih6WkCVU3Wa3BqVKDKlJUsHRcUYznKQOiz5ypW4aq8TxHCfObsciP5cY1eS9-p7UNIp66sJ_SWCRD0AozKB3Yta816ke4Z6A1QNKGc-VOHsiZ1RB3losl2hV9Ko7Zn9t9OYa3NxU4WWA5BjUobOZKsnIBcd2ZsLFqJjPeWi4Mg2UPCU4oybbSXJn1nJ5wl16N628A15N8vwd6Onue9f-RVWfPw5MmEA-jpuxwa-MOmSDijfVrkGk-l25cNUSnVlvtlWqKR2bWjMj8eSj4aGTvsU8i8yLmqX7ITizOwA-hv29AOynOKmXbYgLhU4JrpVZKoxQpXawRAEnGJwx8cU0-oUwlDMqFlmHzjNqga8RKZjvVfrdGZELFqlKGLHQZfHSaL3WUVbYYFYKFZ3IAGSJl9QEi4ILV2JueDgve6PuQ81_qfWkwETwcqYk7JRDZIi2StFANy31kQ4x3jRIBBdUCi0j5ycXxr_aOyq50d9zGyZy1MyqpGalqAx8rYH0pFTDxZLgRCgPWl5hnllupNotYzZDTnurK-IjS8ibj4Xarmbxzlp94v6FVjYJMI7ZsNLj-QcuD2klGnP23UXZyMaCbFXHEz3qtYyWomFS1J-CKSVVeq8NZhKG-7F0yhN69HN4rOYsjIVxp1ELpuAB6OmckqeyAO5ECFsRJO0RWhsQCoxIznyGWCsckXMYGddq7xvbaPIlM9fz8F3hvGSD8m6Yl4uayXJQBWaWkCMGz78QlziiW-wnKFipq3jIhS9bL9IAUPMzxDyPVMuBdRM9vOeN2BYicllXK69OsyjqQ7T_-vjxDoa5GeeZcaHYSzpFDjfCYXzVowgdfE7piBMTtEZggRKf4fSx8RNJ_sTAUr1X3oRUQPVlrMhpekSzxvO_lbGwVplMe2fUqhDT5j_MSJPyr7c50qFxIQfOUFOa_-UVVmrrtkuPcEshnoHnjShJFK_fqRt9Dv-t-RUIVDl3epCV4UOH7qGSbH_CpJ-23oxayR-SUVDV9EftLSvBfYjzLygkAJFRQVfdZMFDwZz7VJh_-SdYf_r-YW_AhWcX8pXTMdeA6jzvBYsQuW9WURiKT7vRGgEUeJqz05ggbEym2XUuZmiMaOqau9KBd-3MMbQFCRk0BjjgfGVcyQHc57izio2YEQqMOvLA7LDWg_MXmjtbgVKUX6WVyl "SVG image of Class Hierarchy")

### Platform Management

### Pollable Interface

### LoRaWAN Support

### FRAM Storage Management

Many MCCI Catena models include FRAM storage for keeping data across power cycles without worrying about the limited write-tolerance of EEPROM or flash. (FRAM, or ferro-electric RAM, is essentially non-volatile memory that can be freely written. Flash EPROM and EEPROM can be written, but tend to have non-local error properties and limited write durability. They are good for storing code, but troublesome for storing counters, because a location must be updated each time a counter is written.)

The abstract class `cFram` is used to represent a FRAM-based storage element. It is abstract in that is uses several virtual methods that must be supplied by the concrete class that represents the specific FRAM chip. (For example, `cFram2K` represents a 2k by 8 FRAM.)

#### FRAM Storage Formats

All FRAMs managed by `cFram` use a common object format on the FRAM, defined by the header file `Catena_FramStorage.h`.

- Storage is viewed as a linear sequence of objects.

- Each object uses a common format.

- Each object consists of a common 24-byte header followed by a variable-length storage field.

- Objects are always a multiple of 4 bytes long.

- Objects are identified by "globally unique ID" (or GUID) and "key" (an 8-bit value). GUIDs are 16-byte values, generated by a standard algorithm with low likelihood of collision. We considered using one GUID for each object, but that would consume a lot of room in system flash memory. So instead, we use an extra one-byte key, which allows most objects to share a common GUID. This approach allows for more space-efficient code on systems with limited system memory.

Each standard object contains a data payload. For any given object, the payload size is fixed when the object is created.

Objects normally contain two payload slots. The slots are written alternately (so that the old version is always available). A voting scheme is used to determine which slot is currently live. Three bytes are used for storing the "current" slot indicator, and are updated only after the new data have been written. A system interruption before the second byte of the trio is written will cause the system to use the old value after recovering from the problem; a system interruption after the second byte of the trio is written will cause the system to use the new value.

The first `uint32_t` of an object records the overall size of the object, and the size of each data payload slot.  Objects are always required to be a multiple of 4 bytes long, so the size is recorded as a count of `uint32_t` values. Objects are allowed to be up to 2^18 bytes long. Data payload fields are specified in bytes, and are limited to [0..32767] bytes.

There is an escape clause. If bit 31 of the first `uint32_t`is set, the object is not "standard". In such a case, the contents of the object after the standard header cannot be used for a standard data payload (as defined above). This may be desirable payloads that are written only once, when the FRAM is intialized; but it leaves redundancy management to the client.

This format is summarized in the following tables.

##### Object Storage Structure

| Bytes | Name | Type  | Description |
|:-----:|:----:|:-----:|:------------|
| 0..3  | `uSizeKey` | `uint32_t` | The size of the overall object, and the size of a datum within the object. This item is stored in little-endian format.  The bit layout is shown below. |
| 4..19 | `Guid` | `MCCIADK_GUID_WIRE` | the 16-byte globally-unique ID of the object. This GUID is stored in _wire_ order (big endian). |
| 20 | `Key` | `uint8_t` | An additional byte of name, allowing up to 256 objects to be defined by a single common GUID. |
| 21..23 | `uVer[3]` | `uint8_t[3]` | Array of current slot indicators. Normally these are all identical and either 0x00 or 0x01. However, after a system upset, it is possible that these will not be the same. If `uVer[0]` is equal to `uVer[1]`, then the slot is selected by the value of these bytes. Otherwise, the slot is selected by the value of `uVer[3]`. |
| 24.._size_-1 | - | - | Reserved space for the data payload. Slot zero starts at byte 24 and runs for the number of data bytes defined by bits 30..16 of `uSizeKey`. Slot one starts immediately after slot zero. |

##### Bit layout of `uSizeKey`

| Bits | Name | Mask | Description |
|:----:|:----:|:----:|:------------|
| 15..0 | `Size` | `cFramStorage::SIZE_MASK` | The size of the object in "clicks". Each click is four bytes. |
| 30..16 | `DataSize` | `cFramStorage::DATASIZE_MASK` | The size of the object's data payload in bytes. This may be zero. |
| 31 | `fNonStandard` | `cFramStorage::NONSTD_MASK` | If zero, the object's payload uses the redundant scheme described above; the payload size is necessarily limited to 32767 byes. If non-zero, the object's payload uses a client-supplied encoding and representation; but can use up to 256 kbytes (since the object size can represent up to 256 kbytes) |

##### The FRAM header object

An FRAM store managed by this library is expected to begin with a header object. A header object is identified by the well-known GUID `{1DE7CDCD-0647-4B3C-A18D-8138A3D9613F}` and the key `kHeader` (zero).

The header object carries a single 4-byte (`uint32_t`) payload, which is interpreted as the end-of-storage address -- the offset of the first byte on the FRAM that is not used for object storage. If an object is added to the store, this pointer is updated after the new object object has been fully committed. The new object is not permanently committed until the end-of-storage pointer is atomically updated.

#### Adding FRAM objects

1. Determine the GUID and key you want to use. If you are adding the item as part of the Catena library, you can use the GUID `GUID_FRAM_CATENA_V1(WIRE)`, `{1DE7CDCD-0647-4B3C-A18D-8138A3D9613F}`; add the key to `McciCatena::cFramStorage::StandardKeys`, defined in `Catena_FramStorage.h`.

   There is no presentable way to use a non-standard GUID; several changes must be made in `Catena_Fram.cpp` to enable this.

2. Ultimately, the metadata for your new object is represented by a 32-bit value of type `cFramStorage::StandardItem`. The constructor takes three (optionally four) arguments:

   - `uKey`, the 8-bit key value
   - `uSize`, the 16-bit object size. (If your object is variable size, you must specify a maximum size, and the actual size of the object must be represented as part of the object data somehow.)
   - `fNumber`, a boolean value. If true, then the value represents a little-endian value; if false, big-endian. This is used for displays and the command interpreter.
   - Optionally `fReplicated` (assumed `true`), which controls whether the replicated data-storage scheme should be used.

3. Find the table `McciCatena::cFramStorage::vItemDefs[]` in `Catena_FramStorage.cpp`, and add your `StandardItem` value at the appropriate offset.

4. To query the value of your object, you can use `gCatena.getFram()->getField(uKey, Value)`; this is a templated function which will set Value according toe the curent value stored for `uKey`.

   - You may also use `gCatena.getFram()->getField(uKey, (uint8_t *)&buffer, sizeof(buffer))`.

5. To set the value of your object, you can use `gCatena.getFram()->saveField(uKey, Value)`; this is a templated function which will write Value to the object identified by `uKey`.

   - You may also use `gCatena.getFram()->saveField(uKey, (const uint8_t *)&buffer, sizeof(buffer))`.

#### Class hierarchy within the FRAM library

<!-- The following image renders well on github, but doesn't render in the previewer in vscode unless you turn on "insecure content". Of course, github rendering is more important, but this is irksome -->
[![Image of cFram -- see assets/cfram.plantuml](http://www.plantuml.com/plantuml/png/ZLLXRzem4FsUNs5fqihAK3KcJHDKKoiw9CJGAjZwPPgYmpRKKcmZsw5YZF--ivCGGaEoBpHzztn-xt4Nxgm3urAPH3TNv341vNxElX4XOSt9IXiodj_FegkRI87aTWEKancbOWIEAo3x29RM6Q2Eq0Ii9VIH6oii5jt2QUERx2D2klk2To1RWTT1GfPQumTV2zLvDspY22MSW4JyuIr4mortRSti4xPYhQmv1xQxpDfgmL3OrlV2A3pn44Krxc__zdg4ZWt8YBmAoyDPFXT3QKxYelq6pmr66znLOx0e8NPu8zGaQITPzSM8khF1THxFOF1zjKBLPCsTBMq5QS3OI4i9YjcY2Owg4_H0StpXK80S38x_WaijOVeXbPks8zKJyzFel7aBMpuMF2diEIut2KP1Rjrkm_qka1zVI2qrY4S_xSThc6y29kDL-5eyK1kNZ7Lu605zvhz-UrugbFiS-rBwn4rU63Pqu8fbpu4Kh2GQM3YPYmbW6AjNQ85zLSxaurD_4II9fiSXolo5oPXWA0_WeDYTSYNwKxyKtRDTw9uFNG6KSzPjdQtUFOELIOMB_NijdlH7cCJpIn0Gjh7Sr_wq8Wfd9ZKMNuX7QHIL51VdoxJKgM8L93D_YkLnLANY92e6XlbG_fCwvJjRKj4afY0hmUJOqVoHsIc6vVfzligLigz-x7UoFyXwMrOtgUjGhQmZ3IsGrDG2ZENuQabvHIp-raXm9Twx793NE2dCPZnoBUEDV_28l_N3fsmN5jYzmFBrmE3E45oO0WbgY_KQdin5hpe6MBd33SBVpNy0)](https://www.plantuml.com/plantuml/svg/ZLLXRzem4FsUNs5fqihAK3KcJHDKKoiw9CJGAjZwPPgYmpRKKcmZsw5YZF--ivCGGaEoBpHzztn-xt4Nxgm3urAPH3TNv341vNxElX4XOSt9IXiodj_FegkRI87aTWEKancbOWIEAo3x29RM6Q2Eq0Ii9VIH6oii5jt2QUERx2D2klk2To1RWTT1GfPQumTV2zLvDspY22MSW4JyuIr4mortRSti4xPYhQmv1xQxpDfgmL3OrlV2A3pn44Krxc__zdg4ZWt8YBmAoyDPFXT3QKxYelq6pmr66znLOx0e8NPu8zGaQITPzSM8khF1THxFOF1zjKBLPCsTBMq5QS3OI4i9YjcY2Owg4_H0StpXK80S38x_WaijOVeXbPks8zKJyzFel7aBMpuMF2diEIut2KP1Rjrkm_qka1zVI2qrY4S_xSThc6y29kDL-5eyK1kNZ7Lu605zvhz-UrugbFiS-rBwn4rU63Pqu8fbpu4Kh2GQM3YPYmbW6AjNQ85zLSxaurD_4II9fiSXolo5oPXWA0_WeDYTSYNwKxyKtRDTw9uFNG6KSzPjdQtUFOELIOMB_NijdlH7cCJpIn0Gjh7Sr_wq8Wfd9ZKMNuX7QHIL51VdoxJKgM8L93D_YkLnLANY92e6XlbG_fCwvJjRKj4afY0hmUJOqVoHsIc6vVfzligLigz-x7UoFyXwMrOtgUjGhQmZ3IsGrDG2ZENuQabvHIp-raXm9Twx793NE2dCPZnoBUEDV_28l_N3fsmN5jYzmFBrmE3E45oO0WbgY_KQdin5hpe6MBd33SBVpNy0 "SVG image of cFram hierarchy")

<!-- The following image renders well on github, but doesn't render in the previewer in vscode unless you turn on "insecure content". Of course, github rendering is more important, but this is irksome -->
[![Image of FRAM Storage objects -- see assets/cframstorage.plantuml](http://www.plantuml.com/plantuml/png/ZLJRJXin47tVhx3sXPjMY29LA5GLRI8GQjDKYU05eMhYdGrkrjx85mga_7jjxoKsMQA-9CgSCpDdpZXpeJH8RNYP7E-HdoK8VJF-JXY71PAYakHo-cMSx1qd0ZYg5L0aOqhP43GA8EiaeIKeHUYb13xJbNHfwuIG8nI6ava6aOFCl-6pSa7zlC8S2sAOqASVVcaoAGg5-jnXQoj4C_fAAw5qbtcjaPD7zpd2GjtTEshosjTsC8Xod8YiwyDXYRTG6jm_yCqwO85wnbxQSAZNGVQxGUPLLHAcVXW-Hnd7fhWg6RM6v4sydk3gvdf43csHAyCQPAF7U37dxqqocVz6ggVmf_Poa-QqMb4kwEkxsYtZp14QiFjzY_Bkz3vGsuwuV-2bzhJrebjQ7RBadKetCay-rgRMyThQ21Fur83rxeE5nBb3Q-fIXLQhk6oSzm3AUihoFipM78660FBrE6ZwW6gpdoER4A-zVPI1VFk0ysrjZwvtNvEUzs64OWk1EH4D9BHw-ouhRywaw1W1uQmUQMYan2r0lGUuhOwOef9n9i3kxwifYkujAokxSMgR4ypKy5fv4Nchr5Psg2LgNribc6RMnxS6-hswa7k3uQ59Jr9oc6MVIReSmrEwwnmCmYEo-tpuOnKtyat-bnt-VJ_zpJAIzg5fajXvBb3azlR-0m00)](https://www.plantuml.com/plantuml/svg/ZLJRJXin47tVhx3sXPjMY29LA5GLRI8GQjDKYU05eMhYdGrkrjx85mga_7jjxoKsMQA-9CgSCpDdpZXpeJH8RNYP7E-HdoK8VJF-JXY71PAYakHo-cMSx1qd0ZYg5L0aOqhP43GA8EiaeIKeHUYb13xJbNHfwuIG8nI6ava6aOFCl-6pSa7zlC8S2sAOqASVVcaoAGg5-jnXQoj4C_fAAw5qbtcjaPD7zpd2GjtTEshosjTsC8Xod8YiwyDXYRTG6jm_yCqwO85wnbxQSAZNGVQxGUPLLHAcVXW-Hnd7fhWg6RM6v4sydk3gvdf43csHAyCQPAF7U37dxqqocVz6ggVmf_Poa-QqMb4kwEkxsYtZp14QiFjzY_Bkz3vGsuwuV-2bzhJrebjQ7RBadKetCay-rgRMyThQ21Fur83rxeE5nBb3Q-fIXLQhk6oSzm3AUihoFipM78660FBrE6ZwW6gpdoER4A-zVPI1VFk0ysrjZwvtNvEUzs64OWk1EH4D9BHw-ouhRywaw1W1uQmUQMYan2r0lGUuhOwOef9n9i3kxwifYkujAokxSMgR4ypKy5fv4Nchr5Psg2LgNribc6RMnxS6-hswa7k3uQ59Jr9oc6MVIReSmrEwwnmCmYEo-tpuOnKtyat-bnt-VJ_zpJAIzg5fajXvBb3azlR-0m00 "SVG image of cFramStorage class hierarchy")

### Asynchronous Serial Port Command Processing

The Catena Aruduino platform provides both an asynchronous command-line collection object and a full command parser.

The `Catena::begin()` method normally crates a commmand parser instance that's linked to a command parser instance. For

#### Collecting lines asynchronously from streams

The header file `Catena_StreamLineCollector.h` defines the class `cStreamLineCollector`. This class is a `cPollableObject`, and as such is polled automaticaly by the governing `cPollingEngine`. A read is launched by calling `cStreamLineCollector::readAsync()`, passing a callback function, a buffer (base and size), and a context handle. When a command has been accumulated, the specified callback function is called according to the following prototype:

```c++
typedef void (cStreamLineCollector::ReadCompleteCbFn)(
    void* pCtx,
    cStreamLineCollector::ErrorCode uStatus,
    uint8_t *pBuffer,
    size_t nBuffer
    );
```

- `pCtx` is the user-supplied context parameter passed to `cStreamLineCollector::readAsync`.
- `uStatus` indicates whether the read was successful, and gives a rough idea of the failure reason if not.
- `pBuffer` points to the first byte of data. This might be `nullptr` in case of error, and it might be different than the user's original buffer pointer.
- `nBuffer` is passed as the actual number of data bytes in the buffer. In case of error, `nBuffer` will be zero.

#### The command parser

A command parser is initialized with a reference to a  `cStreamLineCollector` instance and a convenience reference to the governing `cCatena` instance. It is initialized with

```c++
bool cCommandParser::begin(cStreamLineCollector *pStream, cCatena *pCatena)`
```

The command parser works by parsing the input line into words, and then finding the command in _command tables_, which the client registers at run time using the following function:

```c++
void cCommandParser::registerCommands(cDispatch *pDispatch, void *pContext);
```

Multiple command tables can be registered dynamically; this allows modules to add commands as they are initailized. There's no need to edit a central command table.

The command tables consist of a top-level `cCommandParser::cDispatch` instance. This is **not** a `const` -- it has bookkeeping entries to help with building the tables at runtime without requiring `malloc()`. The dispatch instance points in turn to a

```c++
static cCommandStream::cDispatch myTable(/* cCommandStream::cEntry * */&table, sizeof(table));
```

or

```c++
static cCommandStream::cDispatch myTable(/* cCommandStream::cEntry * */&table, sizeof(table), "groupname");
```

In the first case, the commands are each entered into the top-level name space.  In the second case, a top-level command named `groupname` is entered, and each of the commands in the table is entered as a secondary command.

The command tables themselves are simple arrays of name/function pointer pairs.

```c++
static cCommandStream::CommandFn function1, function2 /*, etc. */;

static const cCommandStream::cEntry table[] = {
	"cmd1", function1,
	"cmd2", function2,
	// ...
};
```

### `Catena_functional.h`

This wrapper allows the C++ `<functional>` header file to be used with Arduino code.

The technical problem is that the `arduino.h` header file defines `min()` and `max()` macros. This causes problems with parsing the `<functional>` header file, at least with GCC.

The solution is a hack: undefine `min()` prior to including `<functional>`, and then redefine them using the well-known definitions.

## Command Summary

### Standard commands

The following commands are supported by the Catena command parser.

| Command | Description |
|-------------|----------------------------------|
| `echo` _args_ | write arguments to the log stream
| `help` | list the known commands |
| `system configure operatingflags` _[&nbsp;uint32 ]_ | display or set the operating flags for this system. |
| `system configure platformguid`  _[&nbsp;hexGuid ]_ | display or set the platform GUID for this system |
| `system configure syseui` _[ eui64 ]_ | display or set the system serial number, a 64-bit number.
| `system reset` | dynamically restart the system, as if the reset button were pressed |

### FRAM commands

| Command | Description |
|-------------|----------------------------------|
| `fram reset` _[_ `hard` _]_ | reset the contents of the FRAM. A soft reset assumes that the datastructures are correct, and resets values to defaults. A hard reset invalidates the FRAM, so that the next boot will fully reconstruct it. |
| `fram dump` _[ base [ len ] ]_ | dump the contents of FRAM, starting at _base_ for _len_ bytes. If _len_ is absent, a length of 32 bytes is assumed. If _base_ is also absent, then 32 bytes are dumpped starting at byte zero.

### LoRaWAN commands

The following commmands are added by the Catena LoRawAN module.

| Command | Description |
|-------------|----------------------------------|
| `lorawan configure` _param [ value ]_  | Display or set a LoRaWAN parameter.

#### LoRaWAN Parameters

Notes that these parameters are generall not loaded into the LMIC immediately. They are primarily used at boot time and at join time.

| Command     | Target device type | Description |
|-------------|---------------------|----------------------------------|
`lorawan configure deveui` _[ value ]_	| OTAA | Set the devEUI for this device to _value_, a 64-bit EUI given in big-endian (natural) form.
`lorawan configure appeui` _[ value ]_	| OTAA |Set the AppEUI for this device to _value_, a 64-bit EUI given in big-endian (natural) form.
`lorawan configure appkey` _[ value ]_	| OTAA |Set the AppKey for this device to _value_, a 128-bit value given in big-endian (natrual) form.
`lorawan configure nwkskey` _[ value ]_	| ABP | Set the NwkSKey for this device (the network session key) to _value_.  For OTAA devices, this reflects the value saved after them most recent join.
`lorawan configure appskey` _[ value ]_	| ABP |Set the AppSKey for this device (the application session key) to  _value_. For OTAA devices, this reflects the value saved after them most recent join.
`lorawan configure devaddr` _[ value ]_	| either | Set the device address, a 32-bit number, in big-endian form. **_Setting devaddr to zero on an OTAA device will cause the LMIC to try to rejoin after the next restart._** For OTAA devices, this reflects the value saved after them most recent join.
`lorawan configure netid` _[ value ]_	| either | Set the network ID, in big-endian form. For OTAA devices, this reflects the value saved after them most recent join.
`lorawan configure fcntup` _[ value ]_	| either | the curent uplink framecount, `FCntUp` in the LoRaWAN spec.
`lorawan configure fcntdown` _[ value ]_ | either | the current downlink framecount, `FCntDown` in the LoRaWAN spec.
`lorawan configure join` _[ value ]_ | either | if zero, the provisioning data will _not_ be loaded into the LMIC at startup. Older versions of the [arduino-lorawan](https://github.com/mcci-catena/arduino-lorawan) might still allow transmits to cause the device to start trying to join, but it will use invalid credentials.

## Example sketches

### `catena_hello`

This is a very simple sketch without LoRaWAN support. It shows the minimal boilerplate needed to use this library. Although it's not obvious, while looping, the program automatically flashes the LED and accepts commands from the console.

### `catena_hello_lora`

This sketch adds LoRaWAN uplink to the basic hello-world application. If the LoRaWAN system is provisioned, the app transmits a single message to port 1, containing the bytes `0xCA`, `0xFE`, `0xBA`, and `0xBE`, in sequence.

If the LoRaWAN system is not provisioned, the application enteres an idle loop; you can use the LoRaWAN commands to set things up.

### `catena_usercommand`

This sketch is very similar to `cathea_hello`. It shows how to add a user-defined comamand, `application hello`, that prints "`Hello, world!`".

## Board Support Dependencies

## Other Libraries and Versions Required

| Library | Recommended Version | Minimum Version | Comments |
|---------|:-------:|:----:|----------|
| [arduino-lmic](https://github.com/mcci-catena/arduino-lmic) | HEAD | 2.1.0 | Earlier versions will fail to compile due to missing `lmic_pinmap::rxtx_rx_polarity` and `lmic_pinmap::spi_freq` fields. |
| [arduino-lorawan](https://github.com/mcci-catena/arduino-lorawan) | HEAD | 0.5.3 | Needed in order to support the Murata module used in the Catena 4551, and for bug fixes in LoRaWAN::begin handling. |
| [catena-mcciadk](https://github.com/mcci-catena/Catena-mcciadk) | 0.1.2 | 0.1.2 | Needed for miscellaneous definitions |

## Library Release History

- HEAD includes the following changes.

  - [#136](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/136) Makes CS pin an input when powering down; use HAL_RCC_GetHCLKFreq().
  - [#125](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/125) Turn on and off HSI clock as needed if system clock is using MSI clock.
  - [#127](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/127) Improve，stabilize AnalogRead() API.

- v0.14.0 (2019-02-10) includes changes for the following issues.

  - [#65](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/65) refactors the stm32/samd code so that code common for the two ports only appears once.
  - [#117](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/117) adds `Catena::ReadAnalog()` method for STM32 that reads the analog reference and adjust the raw ADC counts.
  - [#119](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/119) corrects an error that prevented provisioning on MCCI Catena 4612 and 4801 boards.

- v0.13.0 incorporates recent bug fixes and enhancements. We added our own implementation of the RTC class, to avoid the hacks we were using with the RTCzero library (issue [#86](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/86). We updated the UML docs (issue [#111](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/111)). We refactored the STM32 classes (issue [#99](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/99) and [#103](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/103)). A few other minor changes ([754f4b](https://github.com/mcci-catena/Catena-Arduino-Platform/commit/754f4bd9048f12edbd89906daea483eec31a9468) and [71d45d0](https://github.com/mcci-catena/Catena-Arduino-Platform/commit/71d45d0882b00cc0f18458a35a1f6b320e106433)).

- v0.12.0 adds support for the 4610, 4611, 4612, and 4801, and relies on the LMIC 2.3 pre-integrated pinmap feature to simplify maintenance and make things more structures. We added more UML diagrams to document the class hierarcy. Now depends on MCCI SAMD BSP 1.2.0 and STM32 2.0.0. A common `Catena::Sleep()` method was added for architecture-neutral low-power standby (issue [#83](https://github.com/mcci-catena/Catena-Arduino-Platform/issues/83)). Added experimental machineQ network support. Various minor bug fixes and enhancements.

- v0.11.0 adds a flash driver for the Catena 4470, adds a flash object for storing BME680 calibration data, and fixes bugs.

- v0.10.0 adds explicit support for the Catena 4470, and fixes minor issues.

- v0.9.0 adds explicit support for the Catena 4460.

- v0.8.1 corrects an issue with the STM32 library (some things were here that beloned in the main Arduino libraries).

- v0.8.0 has some minor changes (add the Catena4551 m101/m102/m103/m104 platform, add the Catena4450 m103/m104), and a flag change which effectively changes the API (hence the bump). We add `CatenaBase::fHasLuxS1113`, which indicates the presence of a SI 1113 Lux sensor (as distinct from the BH1750 or the TSL2561 lux sensor used in the Catena4410). Further, we correct the platform flags for the 4551, as it doesn't have an I2C mux. Also incorporates some minor bug fixes for USB serial.

- v0.7.0 is a major refactoring adding support for the `Catena 4551`, which is based on the STM32L0. Although we think that there are no breaking changes, there might be a few, especially if code relied on structured defined internally to the MCCI-Catena-Arduino library `Catena...` classes.
