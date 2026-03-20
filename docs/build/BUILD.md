# Building a simple eBaghet / eChanter-style chanter

This guide rewrites and updates the most useful hardware ideas from the archived **eChanter v3** build notes, using the Nano-based PVC build shown in the photo sequence below.

It is **not** a verbatim copy of the original page. It is an updated practical guide for a simple DIY build that matches this repository more closely.

Archived reference:
- <https://web.archive.org/web/20221204162813/http://www.echanter.com/home/howto-build>

This example build uses:

- a straight PVC tube body
- an Arduino Nano
- direct finger contacts
- a compact headphone jack sub-assembly
- a single-cell battery holder with a 5 V boost converter
- a power switch
- a pressure sensor board at the opposite end of the tube

> Safety note  
> Drilling, cutting, soldering, batteries and boost converters can all cause damage or injury if handled badly. Build and use this project entirely at your own risk.

---

## 1. Overview

The original eChanter guide was designed around a low-cost, easy-to-build electronic chanter body made from PVC or sprinkler-style parts, with direct finger sensors and an Arduino-compatible board.

That basic idea still works very well.

For the **software side**, follow the current **eBaghet** repository and its current Mozzi-based configuration. Do **not** follow the old archived instructions about editing `mozzi_config.h` or using the old legacy Mozzi setup.

---

## 2. Main parts

Suggested parts for a simple build like this:

- 1 PVC tube for the chanter body
- 1 Arduino Nano or compatible board
- 8 finger contacts
- insulated hookup wire
- 1 mono or stereo headphone jack
- passive components for the audio output filter / mixer
- 1 power switch
- 1 single-cell battery holder
- 1 boost converter to 5 V
- 1 pressure sensor board or module
- end caps or housings for the top and bottom ends

Useful tools:

- drill and drill bits
- soldering iron and solder
- wire stripper / cutter
- pliers
- ruler or caliper
- marker for layout lines
- hot glue, epoxy or another strain-relief method

### Parts overview

![Parts laid out before drilling and assembly](01-parts-overview.jpg)

---

## 3. Hole layout

Mark a straight center line along the **front** of the tube and another line exactly opposite on the **back**.

Use these sensor positions, measured from the **top** of the chanter body:

| Sensor | Distance from top |
|---|---:|
| High A | 71 mm |
| High G | 90 mm |
| F | 111 mm |
| E | 137 mm |
| D | 159 mm |
| C | 180 mm |
| B | 209 mm |
| Low A | 244 mm |

Important:

- **High A** goes on the **back** of the chanter.
- All the other sensors go on the **front**.

### Marking and drilling

Keep the visible sensor holes straight and evenly spaced. Crooked spacing is very noticeable on the finished instrument.

Front sensor layout:

![Front hole positions marked and drilled](02-marking-front-holes.jpg)

Rear High A position:

![Rear hole position for High A](03-marking-back-hole.jpg)

---

## 4. Preparing the body

A simple workflow is:

1. cut the PVC tube to length
2. mark the front and back center lines
3. mark the finger positions
4. drill the visible contact holes
5. drill any extra wiring or switch openings
6. dry-fit the end pieces before permanent wiring

For a first build, a plain straight body is usually better than trying to imitate a traditional acoustic chanter shape.

---

## 5. Finger sensors

The archived eChanter guide described several sensor styles, including screw-and-wire contacts, brass contacts and other simple DIY direct-touch methods.

This build uses a compact direct-contact approach:

- one wire per note
- each wire routed inside the PVC body
- each wire soldered to a small metal contact
- the contacts mounted flush or near-flush through the outer wall

### Practical recommendations

- label every wire before routing it
- leave enough slack at the Nano end
- test continuity before closing the body
- add glue or epoxy inside if any contact can rotate or loosen

### Original eChanter Nano pin order

If you want to follow the archived Nano-style pinout, the finger sensors were assigned like this:

| Finger | Arduino pin |
|---|---:|
| High A | D12 |
| High G | D8 |
| F | D7 |
| E | D6 |
| D | D5 |
| C | D4 |
| B | D3 |
| Low A | D2 |

Check the current `eBaghet_config.h` before soldering permanently, especially if you are changing board family or touch mode.

### Routing the sensor wires

![Sensor wires routed through the body](07-sensor-wires-routed.jpg)

### Preparing the contacts

![Prepared finger contacts before installation](08-finger-contacts-prepared.jpg)

### Installing the contacts

![Finger contacts soldered and fitted into the body](09-finger-contacts-installed.jpg)

### Sensor side complete

![Finger-contact side complete, with the contact heads installed](10-finger-side-complete.jpg)

---

## 6. Audio output

The archived eChanter guide originally used a simple Arduino headphone output and, for the old Mozzi setup, strongly preferred the old two-pin **HIFI** mode on pins 9 and 10.

For the current eBaghet repository, the exact best output mode depends on the board you are targeting, so treat the archived audio wiring as **historical inspiration**, not as a mandatory rule.

This Nano build uses a compact headphone jack sub-assembly with passive parts soldered directly at the jack.

### Audio jack parts

![Audio jack parts before assembly](11-audio-jack-parts.jpg)

### Audio jack assembled

![Audio jack with passive components assembled](12-audio-jack-assembled.jpg)

### Nano plus audio sub-assembly

![Arduino Nano with compact audio jack sub-assembly](13-nano-audio-subassembly.jpg)

### Practical advice

- keep the jack wiring short
- add strain relief after testing
- if you hear buzz or distortion, revisit grounding and filtering
- for future ESP32-S3 builds, prefer I2S audio rather than copying the old Nano output stage blindly

---

## 7. Power system

This build uses a single-cell battery holder feeding a small boost converter, then a switch, then the Nano.

A simple order is:

1. connect the battery holder to the boost converter input
2. connect the boost converter output to the switch and board power lines
3. verify a stable 5 V output before connecting the Arduino
4. mount the battery holder and converter in one end section

### Battery holder and boost converter

![Battery holder and boost converter](04-battery-and-boost-converter.jpg)

### Good habits

- check polarity every time before powering up
- insulate exposed solder joints
- do not force the battery holder into the tube if it stresses the wires

---

## 8. Pressure sensor

The archived eChanter guide used a 5 V pressure sensor read by an Arduino analog input.

In this build, the pressure sensor board is mounted at the opposite end of the chanter from the Arduino, with wires routed back through the tube. A side-mounted switch is also fitted in this area.

### Routing the pressure sensor and switch

![Pressure sensor and switch wiring being routed into the body](05-pressure-sensor-and-switch-routing.jpg)

### Pressure sensor mounted in the end section

![Pressure sensor mounted at the top end of the body](06-pressure-sensor-mounted.jpg)

For the future eBaghet roadmap, pressure sensing matters even more because newer versions are expected to support:

- a more realistic bag pressure model
- pressure-dependent pitch variation
- newer sensors such as the **MPXV7002** family

So for a new build, it is sensible to leave extra room and wiring flexibility at the pressure-sensor end.

---

## 9. Internal wiring and assembly order

A good practical order is:

1. prepare the tube and drill all holes
2. prepare the finger contacts and wires
3. install all sensor wires through the body
4. solder the contact ends
5. prepare the headphone jack sub-assembly
6. prepare the battery holder and boost converter
7. install the switch
8. route all wires to the Nano end
9. solder the Nano connections
10. test every finger input
11. test audio
12. test power switching
13. test pressure input
14. only then glue or secure the parts in place

---

## 10. Dry fit and final assembly

Before final closure, it is worth doing at least one dry fit with all main sections in place.

### Dry fit with both end sections

![Dry fit with both end sections installed](14-dry-fit-complete.jpg)

### Body with end caps fitted

![Body with end caps fitted](15-body-with-end-caps.jpg)

### Finished simple chanter

![Finished simple PVC chanter](16-finished-chanter.jpg)

---

## 11. Final notes

This build is intentionally simple. That is a strength, not a weakness.

It is enough to:

- prove the software and finger logic
- test audio on real hardware
- experiment with pressure input
- provide a cheap mechanical platform before moving to better enclosures or more advanced electronics

If you build a more modern version of eBaghet on STM32, Teensy or ESP32-S3, this same mechanical layout can still be a useful first prototype even if the internal electronics change significantly.
