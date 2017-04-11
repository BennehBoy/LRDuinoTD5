/*
Td5strings.cpp -
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>
#include "td5strings.h"

// Fault codes texts
#ifdef _FAULT_CODES_STRINGS_
const char fault_code_void[]="Unknown";
const char fault_code_01_01[]="1-1 egr inlet throttle diagnostics (L)";
const char fault_code_01_02[]="1-2 turbocharger wastegate diagnostics (L)";
const char fault_code_01_03[]="1-3 egr vacuum diagnostics (L)";
const char fault_code_01_04[]="1-4 temperature gauge diagnostics (L)";
const char fault_code_01_05[]="1-5 driver demand problem 1 (L)";
const char fault_code_01_06[]="1-6 driver demand problem 2 (L)";
const char fault_code_01_07[]="1-7 air flow circuit (L)";
const char fault_code_01_08[]="1-8 manifold pressure circuit (L)";
const char fault_code_02_01[]="2-1 inlet air temp. circuit (L)";
const char fault_code_02_02[]="2-2 fuel temp. circuit (L)";
const char fault_code_02_03[]="2-3 coolant temp. circuit (L)";
const char fault_code_02_04[]="2-4 battery volts (L)";
const char fault_code_02_05[]="2-5 reference voltage (L)";
const char fault_code_02_06[]="2-6 ambient air temp. circuit (L)";
const char fault_code_02_07[]="2-7 driver demand supply problem (L)";
const char fault_code_02_08[]="2-8 ambient pressure circuit (L)";
const char fault_code_03_01[]="3-1 egr inlet throttle diagnostics (L)";
const char fault_code_03_02[]="3-2 turbocharger wastegate diagnostics (L)";
const char fault_code_03_03[]="3-3 egr vacuum diagnostics (L)";
const char fault_code_03_04[]="3-4 temperature gauge diagnostics (L)";
const char fault_code_03_05[]="3-5 driver demand problem 1 (L)";
const char fault_code_03_06[]="3-6 driver demand problem 2 (L)";
const char fault_code_03_07[]="3-7 air flow circuit (L)";
const char fault_code_03_08[]="3-8 manifold pressure circuit (L)";
const char fault_code_04_01[]="4-1 inlet air temp. circuit (L)";
const char fault_code_04_02[]="4-2 fuel temperature circuit (L)";
const char fault_code_04_03[]="4-3 coolant temp. circuit (L)";
const char fault_code_04_04[]="4-4 battery volts (L)";
const char fault_code_04_05[]="4-5 reference voltage (L)";
const char fault_code_04_06[]="4-6 ambient air temperature circuit (L)";
const char fault_code_04_07[]="4-7 driver demand supply problem (L)";
const char fault_code_04_08[]="4-8 ambient pressure circuit (L)";
const char fault_code_05_01[]="5-1 egr inlet throttle diagnostics (C)";
const char fault_code_05_02[]="5-2 turbocharger wastegate diagnostics (C)";
const char fault_code_05_03[]="5-3 egr vacuum diagnostics (C)";
const char fault_code_05_04[]="5-4 temperature gauge diagnostics (C)";
const char fault_code_05_05[]="5-5 driver demand problem 1 (C)";
const char fault_code_05_06[]="5-6 driver demand problem 2 (C)";
const char fault_code_05_07[]="5-7 air flow circuit (C)";
const char fault_code_05_08[]="5-8 manifold pressure circuit (C)";
const char fault_code_06_01[]="6-1 inlet air temp. circuit (C)";
const char fault_code_06_02[]="6-2 fuel temperature circuit (C)";
const char fault_code_06_03[]="6-3 coolant temp. circuit (C)";
const char fault_code_06_04[]="6-4 battery voltage problem (C)";
const char fault_code_06_05[]="6-5 reference voltage (C)";
const char fault_code_06_07[]="6-7 driver demand supply problem (C)";
const char fault_code_06_08[]="6-8 ambient pressure circuit (C)";
const char fault_code_07_01[]="7-1 cruise lamp drive over temp. (L)";
const char fault_code_07_02[]="7-2 fuel used output drive over temp. (L)";
const char fault_code_07_03[]="7-3 radiator fan drive over temp. (L)";
const char fault_code_07_04[]="7-4 active engine mounting over temp. (L)";
const char fault_code_07_05[]="7-5 turbocharger wastegate short circuit (L)";
const char fault_code_07_06[]="7-6 egr inlet throttle short circuit (L)";
const char fault_code_07_07[]="7-7 egr vacuum modulator short circuit (L)";
const char fault_code_07_08[]="7-8 temperature gauge short circuit (L)";
const char fault_code_08_01[]="8-1 air conditioning fan drive over temp. (L)";
const char fault_code_08_02[]="8-2 fuel pump drive over temp. (L)";
const char fault_code_08_03[]="8-3 tacho drive over temp. (L)";
const char fault_code_08_04[]="8-4 gearbox/abs drive over temp. (L)";
const char fault_code_08_05[]="8-5 air conditioning clutch over temp. (L)";
const char fault_code_08_06[]="8-6 mil lamp drive over temp. (L)";
const char fault_code_08_07[]="8-7 glow plug relay drive over temp. (L)";
const char fault_code_08_08[]="8-8 glowplug lamp drive over temperature (L)";
const char fault_code_09_01[]="9-1 fuel used output drive open load (L)";
const char fault_code_09_02[]="9-2 cruise lamp drive open load (L)";
const char fault_code_09_03[]="9-3 radiator fan drive open load (L)";
const char fault_code_09_04[]="9-4 active engine mounting open load (L)";
const char fault_code_09_05[]="9-5 turbocharger wastegate open load (L)";
const char fault_code_09_06[]="9-6 egr inlett throttle open load (L)";
const char fault_code_09_07[]="9-7 egr vacuum modulator open load (L)";
const char fault_code_09_08[]="9-8 temperature gauge open load (L)";
const char fault_code_10_01[]="10-1 air conditioning fan drive open load (L)";
const char fault_code_10_02[]="10-2 fuel pump drive open load (L)";
const char fault_code_10_03[]="10-3 tachometer open load (L)";
const char fault_code_10_04[]="10-4 gearbox/abs drive open load (L)";
const char fault_code_10_05[]="10-5 air conditioning clutch open load (L)";
const char fault_code_10_06[]="10-6 mil lamp drive open load (L)";
const char fault_code_10_07[]="10-7 glow plug lamp drive open load (L)";
const char fault_code_10_08[]="10-8 glow plug relay drive open load (L)";
const char fault_code_11_01[]="11-1 cruise control lamp drive over temperature (C)";
const char fault_code_11_02[]="11-2 fuel used output drive over temperature (C)";
const char fault_code_11_03[]="11-3 radiator fan drive over temperature (C)";
const char fault_code_11_04[]="11-4 active engine mounting over temperature (C)";
const char fault_code_11_05[]="11-5 turbocharger wastegate short circuit (C)";
const char fault_code_11_06[]="11-6 egr inlet throttle short circuit (C)";
const char fault_code_11_07[]="11-7 egr vacuum modulator short circuit (C)";
const char fault_code_11_08[]="11-8 temperature gauge short circuit (C)";
const char fault_code_12_01[]="12-1 air conditioning fan drive open load (C)";
const char fault_code_12_02[]="12-2 fuel pump drive open load (C)";
const char fault_code_12_03[]="12-3 tachometer open load (C)";
const char fault_code_12_04[]="12-4 gearbox/abs drive open load (C)";
const char fault_code_12_05[]="12-5 air conditioning clutch open load (C)";
const char fault_code_12_06[]="12-6 mil lamp drive open load (C)";
const char fault_code_12_07[]="12-7 glow plug relay drive open load (C)";
const char fault_code_12_08[]="12-8 glowplug relay drive open load (C)";
const char fault_code_13_01[]="13-1 cruise control lamp drive over temp. (C)";
const char fault_code_13_02[]="13-2 fuel used output drive over temp. (C)";
const char fault_code_13_03[]="13-3 radiator fan drive over temp. (C)";
const char fault_code_13_04[]="13-4 active engine mounting over temp. (C)";
const char fault_code_13_05[]="13-5 turbocharger wastegate short circuit (C)";
const char fault_code_13_06[]="13-6 egr inlet throttle short circuit (C)";
const char fault_code_13_07[]="13-7 egr vacuum modulator short circuit (C)";
const char fault_code_13_08[]="13-8 temperature gauge short circuit (C)";
const char fault_code_14_01[]="14-1 air conditioning fan drive open load (C)";
const char fault_code_14_02[]="14-2 fuel pump drive open load (C)";
const char fault_code_14_03[]="14-3 tachometer open load (C)";
const char fault_code_14_04[]="14-4 gearbox/abs drive open load (C)";
const char fault_code_14_05[]="14-5 air conditioning clutch open load (C)";
const char fault_code_14_06[]="14-6 mil lamp drive open load (C)";
const char fault_code_14_07[]="14-7 glow plug relay drive open load (C)";
const char fault_code_14_08[]="14-8 glowplug relay drive open load (C)";
const char fault_code_15_02[]="15-2 high speed crank (L)";
const char fault_code_16_02[]="16-2 high speed crank (L)";
const char fault_code_17_02[]="17-2 high speed crank (C)";
const char fault_code_19_02[]="19-2 can rx/tx error (L)";
const char fault_code_19_03[]="19-3 can tx/rx error (L)";
const char fault_code_19_06[]="19-6 noisy crank signal has been detected (L)";
const char fault_code_19_08[]="19-8 can has had reset failure (L)";
const char fault_code_20_01[]="20-1 turbocharger under boosting (L)";
const char fault_code_20_02[]="20-2 turbocharger over boosting (L)";
const char fault_code_20_04[]="20-4 egr valve stuck open (L)";
const char fault_code_20_05[]="20-5 egr valve stuck closed (L)";
const char fault_code_21_04[]="21-4 driver demand 1 out of range (L)";
const char fault_code_21_05[]="21-5 driver demand 2 out of range (L)";
const char fault_code_21_06[]="21-6 problem detected with driver demand (L)";
const char fault_code_21_07[]="21-7 inconsistencies found with driver demand (L)";
const char fault_code_21_08[]="21-8 injector trim data corrupted (L)";
const char fault_code_22_01[]="22-1 road speed missing (L)";
const char fault_code_22_03[]="22-3 vehicle accel. outside bounds of cruise control (L)";
const char fault_code_22_07[]="22-7 cruise control resume stuck closed (L)";
const char fault_code_22_08[]="22-8 cruise control set stuck closed (L)";
const char fault_code_23_01[]="23-1 excessive can bus off (C)";
const char fault_code_23_02[]="23-2 can rx/tx error (C)";
const char fault_code_23_03[]="23-3 can tx/rx error (C)";
const char fault_code_23_04[]="23-4 unable to detect remote can mode (C)";
const char fault_code_23_05[]="23-5 under boost has occurred on this trip (C)";
const char fault_code_23_06[]="23-6 noisy crack signal has been detected (C)";
const char fault_code_24_01[]="24-1 turbocharger under boosting (C)";
const char fault_code_24_02[]="24-2 turbocharger over boosting (C)";
const char fault_code_24_03[]="24-3 over boost has occurred this trip (C)";
const char fault_code_24_04[]="24-4 egr valve stuck open (C)";
const char fault_code_24_05[]="24-5 egr valve stuck closed (C)";
const char fault_code_24_07[]="24-7 problem detected with auto gear box (C)";
const char fault_code_25_04[]="25-4 driver demand 1 out of range (L)";
const char fault_code_25_05[]="25-5 driver demand 2 out of range (L)";
const char fault_code_25_06[]="25-6 problem detected with drive demand (C)";
const char fault_code_25_07[]="25-7 inconsistencies found with driver demand (C)";
const char fault_code_25_08[]="25-8 injector trim data corrupted (C)";
const char fault_code_26_01[]="26-1 road speed missing (C)";
const char fault_code_26_02[]="26-2 cruise control system problem (C)";
const char fault_code_26_03[]="26-3 vehicle accel. outside bounds for cruise control (C)";
const char fault_code_26_07[]="26-7 cruise control resume stuck closed (C)";
const char fault_code_26_08[]="26-8 cruise control set stuck closed (C)";
const char fault_code_27_01[]="27-1 inj. 1 peak charge long (L)";
const char fault_code_27_02[]="27-2 inj. 2 peak charge long (L)";
const char fault_code_27_03[]="27-3 inj. 3 peak charge long (L)";
const char fault_code_27_04[]="27-4 inj. 4 peak charge long (L)";
const char fault_code_27_05[]="27-5 inj. 5 peak charge long (L)";
const char fault_code_27_06[]="27-6 inj. 6 peak charge long (L)";
const char fault_code_27_07[]="27-7 topside switch failed post injection (L)";
const char fault_code_28_01[]="28-1 inj. 1 peak charge short (L)";
const char fault_code_28_02[]="28-2 inj. 2 peak charge short (L)";
const char fault_code_28_03[]="28-3 inj. 3 peak charge short (L)";
const char fault_code_28_04[]="28-4 inj. 4 peak charge short (L)";
const char fault_code_28_05[]="28-5 inj. 5 peak charge short (L)";
const char fault_code_28_06[]="28-6 inj. 6 peak charge short (L)";
const char fault_code_28_07[]="28-7 topside switch failed pre injection (L)";
const char fault_code_29_01[]="29-1 inj. 1 peak charge long (C)";
const char fault_code_29_02[]="29-2 inj. 2 peak charge long (C)";
const char fault_code_29_03[]="29-3 inj. 3 peak charge long (C)";
const char fault_code_29_04[]="29-4 inj. 4 peak charge long (C)";
const char fault_code_29_05[]="29-5 inj. 5 peak charge long (C)";
const char fault_code_29_06[]="29-6 inj. 6 peak charge long (C)";
const char fault_code_29_07[]="29-7 topside switch failed post injection (C)";
const char fault_code_30_01[]="30-1 inj. 1 peak charge short (C)";
const char fault_code_30_02[]="30-2 inj. 2 peak charge short (C)";
const char fault_code_30_03[]="30-3 inj. 3 peak charge short (C)";
const char fault_code_30_04[]="30-4 inj. 4 peak charge short (C)";
const char fault_code_30_05[]="30-5 inj. 5 peak charge short (C)";
const char fault_code_30_06[]="30-6 inj. 6 peak charge short (C)";
const char fault_code_30_07[]="30-7 topside switch failed pre injection (C)";
const char fault_code_31_01[]="31-1 inj. 1 open circuit (L)";
const char fault_code_31_02[]="31-2 inj. 2 open circuit (L)";
const char fault_code_31_03[]="31-3 inj. 3 open circuit (L)";
const char fault_code_31_04[]="31-4 inj. 4 open circuit (L)";
const char fault_code_31_05[]="31-5 inj. 5 open circuit (L)";
const char fault_code_31_06[]="31-6 inj. 6 open circuit (L)";
const char fault_code_32_01[]="32-1 inj. 1 short circuit (L)";
const char fault_code_32_02[]="32-2 inj. 2 short circuit (L)";
const char fault_code_32_03[]="";   // fake due to unknown downloading error
const char _fault_code_32_03[]="32-3 inj. 3 short circuit (L)";  // duplicated and renamed due to unknown downloading error
const char fault_code_32_04[]="32-4 inj. 4 short circuit (L)";
const char fault_code_32_05[]="32-5 inj. 5 short circuit (L)";
const char fault_code_32_06[]="32-6 inj. 6 short circuit (L)";
const char fault_code_33_01[]="33-1 inj. 1 open circuit (C)";
const char fault_code_33_02[]="33-2 inj. 2 open circuit (C)";
const char fault_code_33_03[]="33-3 inj. 3 open circuit (C)";
const char fault_code_33_04[]="33-4 inj. 4 open circuit (C)";
const char fault_code_33_05[]="33-5 inj. 5 open circuit (C)";
const char fault_code_33_06[]="33-6 inj. 6 open circuit (C)";
const char fault_code_34_01[]="34-1 inj. 1 short circuit (C)";
const char fault_code_34_02[]="34-2 inj. 2 short circuit (C)";
const char fault_code_34_03[]="34-3 inj. 3 short circuit (C)";
const char fault_code_34_04[]="34-4 inj. 4 short circuit (C)";
const char fault_code_34_05[]="34-5 inj. 5 short circuit (C)";
const char fault_code_34_06[]="34-6 inj. 6 short circuit (C)";
const char fault_code_35_01[]="35-1 inj. 1 partial short circuit (L)";
const char fault_code_35_02[]="35-2 inj. 2 partial short circuit (L)";
const char fault_code_35_03[]="35-3 inj. 3 partial short circuit (L)";
const char fault_code_35_04[]="35-4 inj. 4 partial short circuit (L)";
const char fault_code_35_05[]="35-5 inj. 5 partial short circuit (L)";
const char fault_code_35_06[]="35-6 inj. 6 partial short circuit (L)";
const char *fault_code[] = {
  fault_code_01_01, fault_code_01_02, fault_code_01_03, fault_code_01_04, fault_code_01_05, fault_code_01_06, fault_code_01_07, fault_code_01_08,
  fault_code_02_01, fault_code_02_02, fault_code_02_03, fault_code_02_04, fault_code_02_05, fault_code_02_06, fault_code_02_07, fault_code_02_08,
  fault_code_03_01, fault_code_03_02, fault_code_03_03, fault_code_03_04, fault_code_03_05, fault_code_03_06, fault_code_03_07, fault_code_03_08,
  fault_code_04_01, fault_code_04_02, fault_code_04_03, fault_code_04_04, fault_code_04_05, fault_code_04_06, fault_code_04_07, fault_code_04_08,
  fault_code_05_01, fault_code_05_02, fault_code_05_03, fault_code_05_04, fault_code_05_05, fault_code_05_06, fault_code_05_07, fault_code_05_08,
  fault_code_06_01, fault_code_06_02, fault_code_06_03, fault_code_06_04, fault_code_06_05, fault_code_void,  fault_code_06_07, fault_code_06_08,
  fault_code_07_01, fault_code_07_02, fault_code_07_03, fault_code_07_04, fault_code_07_05, fault_code_07_06, fault_code_07_07, fault_code_07_08,
  fault_code_08_01, fault_code_08_02, fault_code_08_03, fault_code_08_04, fault_code_08_05, fault_code_08_06, fault_code_08_07, fault_code_08_08,
  fault_code_09_01, fault_code_09_02, fault_code_09_03, fault_code_09_04, fault_code_09_05, fault_code_09_06, fault_code_09_07, fault_code_09_08,
  fault_code_10_01, fault_code_10_02, fault_code_10_03, fault_code_10_04, fault_code_10_05, fault_code_10_06, fault_code_10_07, fault_code_10_08,
  fault_code_11_01, fault_code_11_02, fault_code_11_03, fault_code_11_04, fault_code_11_05, fault_code_11_06, fault_code_11_07, fault_code_11_08,
  fault_code_12_01, fault_code_12_02, fault_code_12_03, fault_code_12_04, fault_code_12_05, fault_code_12_06, fault_code_12_07, fault_code_12_08,
  fault_code_13_01, fault_code_13_02, fault_code_13_03, fault_code_13_04, fault_code_13_05, fault_code_13_06, fault_code_13_07, fault_code_13_08,
  fault_code_14_01, fault_code_14_02, fault_code_14_03, fault_code_14_04, fault_code_14_05, fault_code_14_06, fault_code_14_07, fault_code_14_08,
  fault_code_void,  fault_code_15_02, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_16_02, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_17_02, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_19_02, fault_code_19_03, fault_code_void,  fault_code_void,  fault_code_19_06, fault_code_void,  fault_code_19_08,    
  fault_code_20_01, fault_code_20_02, fault_code_void,  fault_code_20_04, fault_code_20_05, fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_21_04, fault_code_21_05, fault_code_21_06, fault_code_21_07, fault_code_void,
  fault_code_22_01, fault_code_void,  fault_code_22_03, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_22_07, fault_code_22_08,
  fault_code_23_01, fault_code_23_02, fault_code_23_03, fault_code_23_04, fault_code_23_05, fault_code_23_06, fault_code_void,  fault_code_void,
  fault_code_24_01, fault_code_24_02, fault_code_24_03, fault_code_24_04, fault_code_24_05, fault_code_void,  fault_code_24_07, fault_code_void,
  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_25_04, fault_code_25_05, fault_code_25_06, fault_code_25_07, fault_code_25_08,
  fault_code_26_01, fault_code_26_02, fault_code_26_03, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_26_07, fault_code_26_08,
  fault_code_27_01, fault_code_27_02, fault_code_27_03, fault_code_27_04, fault_code_27_05, fault_code_27_06, fault_code_27_07, fault_code_void,
  fault_code_28_01, fault_code_28_02, fault_code_28_03, fault_code_28_04, fault_code_28_05, fault_code_28_06, fault_code_28_07, fault_code_void,
  fault_code_29_01, fault_code_29_02, fault_code_29_03, fault_code_29_04, fault_code_29_05, fault_code_29_06, fault_code_29_07, fault_code_void,
  fault_code_30_01, fault_code_30_02, fault_code_30_03, fault_code_30_04, fault_code_30_05, fault_code_30_06, fault_code_30_07, fault_code_void,
  fault_code_31_01, fault_code_31_02, fault_code_31_03, fault_code_31_04, fault_code_31_05, fault_code_31_06, fault_code_void,  fault_code_void,
  fault_code_32_01, fault_code_32_02, _fault_code_32_03, fault_code_32_04, fault_code_32_05, fault_code_32_06, fault_code_void,  fault_code_void,
  fault_code_33_01, fault_code_33_02, fault_code_33_03, fault_code_33_04, fault_code_33_05, fault_code_33_06, fault_code_void,  fault_code_void,
  fault_code_34_01, fault_code_34_02, fault_code_34_03, fault_code_34_04, fault_code_34_05, fault_code_34_06, fault_code_void,  fault_code_void,
  fault_code_35_01, fault_code_35_02, fault_code_35_03, fault_code_35_04, fault_code_35_05, fault_code_35_06, fault_code_void,  fault_code_void };
#endif
