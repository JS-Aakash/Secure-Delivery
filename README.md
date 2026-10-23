# Smart Parcel Box Controller

A clean, minimal, zero-dependency static web controller for an ESP32-powered parcel box. Built with vanilla HTML, CSS, and JavaScript.

---

## 🔐 Owner Login Credentials (Hardcoded)

To access the Owner Portal and generate single-use delivery codes, use the following hardcoded credentials (removed from the frontend UI for cleaner presentation):

- **Username:** `owner`
- **Password:** `box123`

---

## 📱 Pages Included

1. **[login.html](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/login.html)** — Dedicated Box Owner Sign In page.
2. **[owner.html](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/owner.html)** — Protected Owner Portal (generate 6-digit OTP, 5-minute countdown, copy code, sign out).
3. **[delivery.html](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/delivery.html)** — Dedicated Delivery Person page (connect ESP32 via USB, enter OTP keypad, unlock `1`, and manual close `0`).
4. **[index.html](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/index.html)** — Combined portal with switcher between Owner (protected by login) & Delivery Person views (hash links: `/#owner` and `/#delivery`).

*(OTPs generated on the Owner portal automatically synchronize with the Delivery page via `localStorage` or URL query parameter `?otp=123456`).*

---

## ⚠️ Important: Why the Browser Cannot Connect If Arduino IDE Is Open

> **Crucial Serial Port Rule on Windows:**
> Operating systems permit only **one** program to access a physical COM port at a time.
>
> If you test the ESP32 in the **Arduino IDE Serial Monitor**, the Arduino IDE locks the COM port. When Chrome or Edge requests the port, the browser pairs with it, but the OS denies the open request with `Access Denied` / `Port Busy`.
>
> **Solution:**
> 1. **Close the Arduino IDE Serial Monitor** (click the `X` on the Serial Monitor tab/window).
> 2. Open the website and click **"Connect Box"**.
> 3. Select the ESP32 port and click **Connect**.
> 4. The button turns green (**Box Connected**), and `sendSerial` will communicate at 9600 baud.

---

## 🌐 How to Host & Run from Anywhere

### 1. Instant Deployment to Netlify
1. Open [https://app.netlify.com/drop](https://app.netlify.com/drop).
2. Drag and drop the `Secure_delivery` folder directly onto the page.
3. You will immediately receive a live public HTTPS address (e.g., `https://smart-parcel-box.netlify.app`).

### 2. Sharing Links
- **For Owner Login:** `https://your-site.netlify.app/login.html`
- **For Courier:** `https://your-site.netlify.app/delivery.html`
- **With Pre-filled Code:** `https://your-site.netlify.app/delivery.html?otp=123456`

---

## ⚡ Firmware Files

- [esp32.ino](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/esp32.ino) — Web Serial firmware (GPIO 4, 9600 baud, `ESP32Servo.h`). For USB connection to local PC/kiosk.
- [esp32_wifi.ino](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/esp32_wifi.ino) — Standalone WiFi firmware for wireless control from any phone without USB cables.
