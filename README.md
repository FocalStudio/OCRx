![OCRx](https://ocrx.focalstudio.me/logo/OCRx_mini.png)
# Introducing OCRx, a all-new optical character recognition system.

![GitHub release](https://img.shields.io/badge/release-v.3.42-red.svg) ![Created](https://img.shields.io/badge/created-may%202018-orange.svg) ![C Standard](https://img.shields.io/badge/c-standard%20c99-blue.svg)


**OCRx**  (for  _Optical Character Recognition eXperience_) is a  [optical character recognition system](https://searchcontentmanagement.techtarget.com/definition/OCR-optical-character-recognition)  developed as part of the EPITA 2nd Year Project. This system is powered by an artificial intelligence composed of a neural network system capable of learning millions of characters, such as the Unicode table.

This software extracts a text present in an image (photograph, digitized text, scanned document) via a segmentation of the image (separation of the different elements constituting the image) and the use of a neural network capable of matching the characters..

## Installation

<ul>
          <li>Download the archive from <a href="https://github.com/mojombo/product/commit/be6a8cc1c1ecfe9489fb51e4869af15a13fc2cd2" class="commit-link"><tt>GitHub</tt></a></li>
          <li>Unzip the archive (using for example <a href="http://www.winzip.com/">Winzip</a>).</li>
          <li>When you are in the <tt>/OCRx</tt> directory, open a Terminal and execute the following commands:</li>
            <pre><code>$ make ocrx</code><br><code>$ ./ocrx</code></pre>
            This will launch the GUI and you will be able to choose an image to detect the characters.</li>
	     <li>You can also compile without the interface (using the directory <tt>/OCRx/process</tt>) by executing the following commands:
            <pre><code>$ make process</code><br><code>$ ./process path_to_the_image</code></pre></li>
        </ul>
        

## Requirements
The use of OCRx requires the installation of 3 C libraries.

-   [SDL 2.0.7](https://www.libsdl.org/ "SDL")
-   [GTK+ 3.22](https://www.gtk.org/ "GTK+")
-   [Gnome Glade 3.20](https://glade.gnome.org/ "GTK+")

## How it works?

Conceptually, the OCR processing flow is as follows:

-   Loading image
-   Deleting colors (grayscale, then black and white)
-   Pretreatment
-   Detection of text blocks
-   Character detection
-   Recognition of detected characters
-   Reconstruction of the text

The division of the image into blocks then into characters (passing through a division of the blocks into lines) is necessary to send to the recognition pieces of images logically corresponding to characters.

Character recognition is the central part of OCR, it requires a learning phase during which the neural network will learn to recognize the different characters.

To launch the program, please refer to section  _Installation_.

## Credits
Made with love by Find3r, El Fantomas, Triguneur and TipChef.

**OCRx** was developed by the [Focal Studio](https://www.focalstudio.me/ "Focal Studio") Project Group in collaboration with [EPITA](http://www.epita.fr/international/ "EPITA"), School of Computer Engineers and member of [IONIS Education Group](https://www.ionis-group.com/ "IONIS Education Group"). For any question, please contact us at [contact@focalstudio.me](mailto:contact@focalstudio.me)
