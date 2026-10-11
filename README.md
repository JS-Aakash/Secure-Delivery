# Smart Parcel Box Controller

A clean, minimal, zero-dependency static web controller for an ESP32-powered parcel box. Built with vanilla HTML, CSS, and JavaScript.

---

## 📱 Pages Included

1. **[index.html](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/index.html)** — Combined portal with clean switcher between Owner & Delivery Person views (hash links: `/#owner` and `/#delivery`).
2. **[owner.html](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/owner.html)** — Dedicated Owner-only page (generate 6-digit OTP, 5-minute countdown, copy code).
3. **[delivery.html](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/delivery.html)** — Dedicated Delivery Person page (connect ESP32 via USB, enter OTP keypad, unlock `1`, and manual relock `0`).

*(OTPs generated on the Owner page automatically synchronize with the Delivery page via `localStorage` or URL query parameter `?otp=123456`).*

---

## 🌐 How to Host & Run from Anywhere

### 1. Instant Deployment to Netlify
1. Open [https://app.netlify.com/drop](https://app.netlify.com/drop).
2. Drag and drop the `Secure_delivery` folder directly onto the page.
3. You will immediately receive a live public HTTPS address (e.g., `https://smart-parcel-box.netlify.app`).

### 2. Sharing Links
- **For Owner:** `https://your-site.netlify.app/owner.html` (or `/#owner`)
- **For Courier:** `https://your-site.netlify.app/delivery.html` (or `/#delivery`)
- **With Pre-filled Code:** `https://your-site.netlify.app/delivery.html?otp=123456`

---

## ⚡ Firmware Files

- [esp32.ino](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/esp32.ino) — Web Serial firmware (GPIO 4, 9600 baud, `ESP32Servo.h`). For USB connection to local PC/kiosk.
- [esp32_wifi.ino](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/esp32_wifi.ino) — Standalone WiFi firmware for wireless control from any phone without USB cables.
