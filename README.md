# PM25andFlulndicator
## ภาพรวมโครงการ

โครงการนี้เป็นการจัดทำระบบที่ทำงานหลายฟังก์ชั่นด้วยกัน โดยระบบจะเก็บข้อมูลฝุ่นควัน PM2.5 อุณหภูมิสภาพแวดล้อม และการวัดไข้เมื่อมีสิ่งของเข้ามาใกล้เซนเซอร์ โดยแต่ละฟังก์ชั่นจะมีขั้นตอนการทำงานดังนี้

 1. **ระบบวัดฝุ่นควัน** ตรวจจับฝุ่นควัน และส่งค่าไปยัง MQTT Server
 2. **ระบบวัดอุณหภูมิสภาพแวดล้อม** ตรวจจับอุณหภูมิสภาพแวดล้อม และส่งค่าไปยัง MQTT Server
 3. **ระบบวัดไข้** ตรวจวัดอุณภูมิสิ่งที่เข้าใกล้เซ็นเซอร์ และแสดงผลอุณหภูมิบนหน้าจอ


## อุปกรณ์ที่ใช้

 1. NodeMCU ESP8266
 2. Infrared temperature sensor (GY 906)
 3. Laser dust sensor (PMS 3003)
 4. Tracking sensor (TCRT 5000)
 5. LED ขนาด 5mm
 6. LCD I2C screen ขนาด 16 x2
 7. ซอฟต์แวร์ Arduino 1.6.8
 8. ESP8266 2.4.2
 9. Python2 หรือ 3
 10. git

## แผงวงจร

ให้เดินสายอุปกรณ์และเซนเซอร์ต่างๆ ตามภาพ

<p align="center">
  <img src="doc/picture003.jpg" width="400" align="center" alt="อุปกรณ์ที่ประกอบเสร็จแล้ว" title="อุปกรณ์ที่ประกอบเสร็จแล้ว" caption="อุปกรณ์ที่ประกอบเสร็จแล้ว">
</p>
<p align="center">
  <img src="doc/picture004.jpg" width="400" align="center" alt="อุปกรณ์ที่ประกอบเสร็จแล้ว" title="อุปกรณ์ที่ประกอบเสร็จแล้ว" caption="อุปกรณ์ที่ประกอบเสร็จแล้ว">
</p>

## จัดทำโค้ดสำหรับโครงการ

### ติดตั้ง Arduino 1.6.8

ดาวน์โหลด Arduino โดยให้เลือกเป็นเวอร์ชั่น 1.6.8

### ติดตั้งบอร์ด ESP8266
 1. เปิดโปรแกรม Arduino ไปที่ Preference
 2. เพิ่ม http://arduino.esp8266.com/stable/package_esp8266com_index.json ลงในช่อง Additional Board Manager
 3. ที่โปรแกรม Arduino เปิดบอร์ด Manager
 4. เลือก esp8266 โดยให้ติดตั้งเวอร์ชั่น 2.4.2
 5. เข้าไปที่โฟลเดอร์ Documents/Arduino/hardware/esp8266com (หากยังไม่มี ให้สร้างโฟลเดอร์ขึ้นมา)
 6. เปิด Terminal เข้าไปที่โฟลเดอร์ข้างต้น พิมพ์คำสั่ง git clone https://github.com/esp8266/Arduino.git esp8266
 7. cd เข้าไปที่โฟลเดอร์ esp8266/tools (Documents/Arduino/hardware/esp8266com/esp8266/tools)
 8. พิมพ์คำสั่ง python get.py

### เขียนโค้ด

 1. ดาวน์โหลดโค้ดของ Git โครงดารนี้ โดยคุณจะเห็นโฟลเดอร์ code
 2. ให้นำไฟล์ทั้งหมดไปไว้ยัง Workspace ของ Arduino แล้วเปิดไฟล์ขึ้นมาแก้ไข
 3. แก้ไขที่ไฟล์ aws.cpp และ random.h
 4. Compile และอัปโหลดลงบอร์ด
