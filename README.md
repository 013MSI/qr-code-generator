# QR Code Generator & Scanner
**Creators:** *Yin-Yang Cats* 🐾 aka Ayesha Ilyas & Maryam Ilyas


## Description
This **terminal-based app** enables users to generate and scan **colored QR codes** that use a unique, custom encoding scheme.

- **Generate**: Enter some text, and the app encodes it into a grid of decimals, outputting a colorful QR code as a bitmap.
- **Scan**: Read QR codes created by the program, decoding their bitmaps back into text.
- **Verify**: A checksum ensures data integrity by providing a way to determine if text matches a QR code.

➡️ Learn more about our custom [encoding scheme](https://013msi.github.io/qr-code-generator/)

## Checksum
-  **What is a checksum?** A checksum is a numerical or alphanumeric value calculated from a block of data. It is primarily used to verify the integrity of data during storage or transmission. By comparing checksums, you can detect errors or alterations in the data. Although checksums are not foolproof, they offer a quick and simple method for basic error detection.
-  **Our Checksum Implementation:** When a QR code is generated, it automatically calculates and outputs a checksum. This checksum serves as a reference to ensure the data remains intact. During decoding, the program generates another checksum based on the decoded data. By comparing these two checksums, users can verify the integrity of the data:
   - If the checksum match, the data has not been tampered with.
   - If the checksums do not match, the data may have been altered or corrupted.
   - An example checksum is: 
      
     ```
     Dhs,d(uut:llu?
     ```

## Core App Components
- **`QRCode`** - contains core logic for generating and scanning qr codes using custom encoding scheme
- **`Image`** - stores RGB pixel data in a grid
- **`Bitmap`** - reads and writes BGR bmp files
- **`Color`** - represents an RBG color
- **`ColorPalette`** - container for multiple **`Color`** objects
- Utility functions for initializing vectors, I/O operations, string manipulation, and more


## Sample QR Codes
Text to encode:
> *Valuable lessons were code words for pain that no one apologized for.*
> ― *Jennifer A. Nielsen, The False Prince*

**Grayscale**

![Sample grayscale QR code](https://raw.githubusercontent.com/013MSI/qr-code-generator/refs/heads/main/samples/qr-grayscale.bmp)

**Autumn Theme**

![Sample autumn QR code](https://raw.githubusercontent.com/013MSI/qr-code-generator/refs/heads/main/samples/qr-autumn.bmp)

**Ocean Theme**

![Sample ocean QR code](https://raw.githubusercontent.com/013MSI/qr-code-generator/refs/heads/main/samples/qr-ocean.bmp)


### **Running the App Locally (for unix systems)**
1. Clone the repository:
   ```bash
   git clone https://github.com/013MSI/qr-code-generator.git
   ```
2. Navigate to the project directory:
   ```bash
   cd qr-code-generator
   ```
3. Run the build script (if on a unix based system which has `cmake` and `make` installed)
    ```bash
    bash scripts/build.sh
    ```

## License
This project is licensed under the **MIT License**.
