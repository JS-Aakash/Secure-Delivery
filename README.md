# Smart Parcel Box Controller

A clean, responsive, zero-dependency static web controller and firmware system for an ESP32-powered parcel drop box. Built with vanilla HTML5, CSS3, and ES6+ JavaScript.

---

## 🔐 Owner Login Credentials (Demo)

To access the Owner Portal and generate single-use delivery codes, use the following demo credentials (intentionally omitted from the public UI for a clean production presentation):

- **Username:** `owner`
- **Password:** `box123`

---

## 📱 Pages Included

| Page | URL Path | Description |
|---|---|---|
| **Unified Portal** | [`index.html`](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/index.html) | Single-page application featuring tab navigation between Courier and Owner modes, real-time status banner, persistent serial manager, and activity logs. |
| **Courier Access** | [`delivery.html`](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/delivery.html) | Minimalist interface for delivery personnel to enter OTP passcodes, connect the box, unlock, and lock the parcel compartment. |
| **Owner Portal** | [`owner.html`](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/owner.html) | Authenticated dashboard to generate 6-digit one-time access codes with 5-minute countdown timers, copy code, and direct link generation. |
| **Owner Sign In** | [`login.html`](file:///c:/Users/jsaak/OneDrive/Desktop/Coding/Secure_delivery/login.html) | Standalone authentication gate for the Box Owner. |

---

## ⚙️ Hardware & Actuation Specifications

The system utilizes a single high-torque SG90 micro servo directly driving the latch bolt:

### 🔌 Wiring & Pinout

| Component Wire | Color | ESP32 Pin | Purpose |
|---|---|---|---|
| **Servo Signal** | Orange / Yellow | **GPIO 4** | 50Hz PWM Control Signal |
| **Servo Power (VCC)** | Red | **VIN / 5V** | 4.8V – 6.0V DC Power |
| **Servo Ground** | Brown / Black | **GND** | Ground reference (common ground) |
| **ESP32 USB** | Micro-USB / Type-C | **PC USB Port** | 9600 Baud Web Serial Communication |

### 🔄 Angle Configuration (Motor Setup)

| Action | Command Sent | Motor Angle | Firmware ACK Response |
|---|---|---|---|
| **Unlock Box** | `1\n` | **0°** | `[ESP32] ACK: UNLOCKED (0 deg)` |
| **Lock Box** | `0\n` | **90°** | `[ESP32] ACK: LOCKED (90 deg)` |

*Default State:* At power-on or microcontroller boot, the servo automatically sets to **90° (LOCKED)**.

---

## 🌐 Production Architecture & Features

1. **Light Beige & Brown Aesthetic:**
   - Calibrated warm palette (`#f6f3ee` page background, `#ffffff` surface cards, `#5c4033` deep espresso primary actions, `#a3693f` warm amber accents).
   - High readability meeting WCAG AAA contrast requirements (>12:1).
   - Modern typography using *Plus Jakarta Sans* and *JetBrains Mono*.

2. **Persistent Web Serial Connection:**
   - Automatically checks `navigator.serial.getPorts()` on page reload. If the device was previously paired and `box_serial_auto` is set, the browser reconnects without displaying the system device chooser again.
   - Automatically handles physical USB `connect` and `disconnect` events.

3. **Persistent Single-Use OTP with Cross-Tab Sync:**
   - Active OTP code and expiration timestamp are stored in `localStorage`.
   - Real-time countdown timer automatically recalculates `(expiresAt - Date.now())` upon refresh.
   - Instant cross-tab and cross-page synchronization using the browser's `BroadcastChannel('parcel_box_channel')` and `window.addEventListener('storage', ...)`.
   - Invalidation is immediate upon use or expiration.

4. **Web Audio Sound Effects:**
   - Built-in synthesized chimes via the Web Audio API for lock/unlock actions and keypad input (can be muted via the sound toggle).

5. **Activity Audit Log:**
   - Client-side event logging of unlocks, locks, OTP generations, and connection events stored in `localStorage` (`box_activity_logs`).

6. **Zero Inline Styles:**
   - All styling is decoupled into scoped CSS utility and component classes, preventing CSP (Content Security Policy) issues.

---

## ⚠️ Important Windows Serial Note

> [!IMPORTANT]
> **Windows COM Port Exclusivity:**
> Windows allows only **one application** to access a physical COM port at any given time.
>
> If you test the ESP32 in the **Arduino IDE Serial Monitor**, the IDE locks the port. When Chrome or Edge attempts to connect, Windows rejects the request with `Access Denied` or `Port Busy`.
>
> **Before opening the website:**
> 1. **Close the Arduino IDE Serial Monitor window.**
> 2. Open Chrome or Edge.
> 3. Click **Connect Box** on the website and select your ESP32.

---

## 🚀 How to Host & Deploy to Netlify

This website requires **no Node.js, no build steps, and no backend server**. It runs purely on the client side over HTTPS.

### Netlify Drag-and-Drop (Netlify Drop)
1. Go to [https://app.netlify.com/drop](https://app.netlify.com/drop).
2. Drag and drop the `Secure_delivery` folder directly into the browser upload box.
3. Netlify will deploy the site in 5 seconds and give you a live HTTPS URL (e.g., `https://smart-parcel-box.netlify.app`).

### Sharing URLs
- **Direct Delivery Page:** `https://your-site.netlify.app/delivery.html`
- **Delivery Page with Pre-filled OTP:** `https://your-site.netlify.app/delivery.html?otp=123456`
- **Owner Login:** `https://your-site.netlify.app/login.html`
- **Unified Interface:** `https://your-site.netlify.app/index.html`

---

## 🛠️ Arduino IDE Setup

1. Open `esp32.ino` in the Arduino IDE.
2. Go to **Sketch** > **Include Library** > **Manage Libraries...**
3. Search for **ESP32Servo** (by Kevin Harrington) and click **Install**.
4. Select your ESP32 board under **Tools** > **Board** (e.g. *ESP32 Dev Module*).
5. Select your COM port under **Tools** > **Port**.
6. Click **Upload** (ensure you press and hold the *BOOT* button on the ESP32 if required during upload).
7. Once uploaded, close the Serial Monitor and open your Netlify or local website in Google Chrome or Microsoft Edge.
