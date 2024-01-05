<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <!-- <a href="https://github.com/mikahas/speede">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a> -->

<h3 align="center">Speede</h3>

  <p align="center">
    An arcade style reaction game built with Arduino.
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

Immerse yourself in the retro thrill of this arcade-style reaction game, featuring buzzer sounds and the satisfying smacks of arcade-style buttons.

Your sole challenge? Keep up with the relentless rhythm of blinking lights. Brace yourself for a rollercoaster of frustration and fun, as this game brilliantly combines a challenge with an irresistibly addictive quality, keeping you coming back for more adrenaline-pumping action.

A special thanks to Spede Pasanen, the Finnish inventor, comedian, and multifaceted personality, whose creativity inspired this exciting journey.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

Download the repo to you computer and open it in the Arduino IDE.

### Prerequisites

You should be familiar with Arduino development and some electronics assembly.

Components needed:
- Arduino Mega 2560
  - Arduino UNO would probably work as well but in that case the seven segment display needs a shift register and the code needs to be changed accordingly
- Piezo buzzer
- Buttons
- LEDs for the buttons
- Resistors for LEDs and the seven segment display
  - Different color LEDs need different resistors so read your datasheets!
- Breadboard for testing things out

Other stuff:
- Soldering iron, wires etc. for basic electronics tinkering
- Acrylic glass and/or wood for making the case
- Charger for standalone fun
  - Arduino Mega recommended input voltage is 7-12v
- Optional: paper, pen etc. art supplies for making cool artwork


### Installation

Hardware schematics:
![Speede schematics](/images/speede_schem.jpg "Speede schematics")

The Arduino code is self contained and no external libraries are needed. I used VSCode to write the program but you should be able to just open the project into the regular old Arduino IDE.

1. Select the correct board (Arduino Mega 2560) 
2. Upload code to the board
3. Play!

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage

Following the startup process, there is a brief initialization phase during which the button LEDs illuminate sequentially. This not only adds a visually appealing touch but also serves the purpose of verifying the functionality of each LED. The game can be initiated by pressing the red button once the initial bootup is complete.

The game involves smacking the buttons as their corresponding LEDs light up. Initially, the delay between smacks is relatively slow, gradually intensifying as the game progresses. The button LEDs illuminate in a random order.

After some vigorous smacking, the inevitable moment arrives, and you lose. There aren't any winners in this game, I suppose. The display reveals the final score, and to begin a new game, simply press the red button once more. It's a mix of fun and frustration!

There are two ways to experience defeat:

1. Failing to smack the buttons in the correct sequence (i.e., pressing the wrong button).
1. The button press sequence reaches its limit. This occurs when the memory storing the order of button presses is full, preventing the game from continuing indefinitely.

If left idle for a while, the game initiates a demo mode, randomly illuminating the LEDs.


<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Artwork

Motivated by Spede Pasanen and the TV game show "Speden Spelit," which aired in Finland during the 90s and early 2000s, I chose to create Spede-themed artwork for the game, adding a unique touch to it.

![Speede](/images/speede.jpg "Speede breadboard and artwork")

<!-- CONTRIBUTING -->
## Contributing

Contribute if you must. Here's a small howto:

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Special thanks to Jaakko Kairus for providing a similar speed game using PIC microcontroller.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/mikahassinen
[arduino-url]: https://www.arduino.cc/



