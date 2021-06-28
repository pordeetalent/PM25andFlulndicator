# MQTT Server
## การใช้งานโค้ด MQTT Server สำหรับโครงการนี้

MQTT Server เป็นรูปแบบการรับและส่งข้อมูลแบบ Client Server ที่เป็นที่นิยมสำหรับการจัดทำโครงงาน IoT โดยรูปแบบการให้บริการคือ MQTT จะมีบริการรับและส่งข้อมูล PubSub โดยที่เราจะทำให้บอร์ด NodeMCU ของเราส่งข้อมูลขึ้นไปยัง MQTT Server ของเรา

## จัดเตรียมสภาพแวดล้อมบน MQTT

ในโครงการนี้ เราจะจัดทำเฉพาะส่วนของ NodeMCU ซึ่งจะทำงานในระดับของ MQTT Client สำหรับ Pub เพื่อส่งค่าไปยัง MQTT Server เท่านั้น ดังนั้นในโครงงานนี้จะถือว่าท่านได้จัดทำ MQTT Server เพื่อรองรับการ Publish ค่าไว้แล้ว โดยท่านจะมีค่าต่างๆ ที่ได้มาดังนี้

1. MQTT Server adress (อาจเป็น IP หรือ Domain)
2. Port สำหรับ Connect
3. Username
4. Password

## จัดเตรียมเครื่องสำหรับเขียนโค้ด

### ซอฟต์แวร์ที่ต้องใช้

- Arduino 1.6.8
- git

### ขั้นตอนการจัดเตรียม

1. ดาวน์โหลด Arduino โดยให้เลือกเป็นเวอร์ชั่น 1.6.8 และติดตั้ง
2. ติดตั้งบอร์ด ESP8266
  - เปิดโปรแกรม Arduino ไปที่ Preference
  - เพิ่ม http://arduino.esp8266.com/stable/package_esp8266com_index.json ลงในช่อง Additional Board Manager
  - ที่โปรแกรม Arduino เปิดบอร์ด Manager
  - เลือก esp8266 โดยให้ติดตั้งเวอร์ชั่น 2.4.2
  - เข้าไปที่โฟลเดอร์ Documents/Arduino/hardware/esp8266com (หากยังไม่มี ให้สร้างโฟลเดอร์ขึ้นมา)
  - เปิด Terminal เข้าไปที่โฟลเดอร์ข้างต้น พิมพ์คำสั่ง git clone https://github.com/esp8266/Arduino.git esp8266
  - cd เข้าไปที่โฟลเดอร์ esp8266/tools (Documents/Arduino/hardware/esp8266com/esp8266/tools)
  - พิมพ์คำสั่ง python get.py

## Library

### ไลบรารี่ที่ต้องใช้

- ติดตั้ง ESP8266WiFi.h       เวอร์ชั่น 1.0.0
- ติดตั้ง PubSubClient.h      เวอร์ชั่น 2.7.0
- ติดตั้ง SoftwareSerial.h    เวอร์ชั่น 1.0.0
- ติดตั้ง Wire.h              เวอร์ชั่น 1.0.0
- ติดตั้ง Adafruit_MLX90614.h เวอร์ชั่น 1.1.1
- ติดตั้ง LiquidCrystal_I2C.h เวอร์ชั่น Unknown

## จัดทำบอร์ด

สำหรับขั้นตอนนี้ เราได้มีอุปกรณ์ NodeMCU พร้อมเดินลายวงจรและเซ็นเซอร์ไว้เรียบร้อยแล้ว โดยดูได้ที่ README.md ของโฟลเดอร์หลักของโครงการ

## จัดทำโค้ดสำหรับโครงการ

เมื่อจัดทำอุปกรณ์เสร็จแล้ว ให้เลือกโค้ดที่จะใช้เพื่ออัปโหลดลงบอร์ด โดยโค้ดจะอยู่ในโฟลเดอร์ code ซึ่งจะมีโค้ดในรูปแบบ MQTT Server ให้เลือกใช้ตามที่ต้องการ

1. ดาวน์โหลดโค้ดของ Git โครงดารนี้ โดยคุณจะเห็นโฟลเดอร์ code ซึ่งจะแบ่งเป็นสองชุด คือโค้ดสำหรับ โครงการแบบ MQTT Server
2. ให้นำไฟล์โค้ด (MQTT Server) ไปไว้ยัง Workspace ของ Arduino แล้วเปิดไฟล์ขึ้นมาแก้ไข
3. ดูการตั้งค่าเพิ่มเติมในเอกสารของโค้ดแต่ละแบบ
4. ตั้งค่า และอัปโหลดโค้ดลงบอร์ด