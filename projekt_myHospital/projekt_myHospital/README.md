
# Hospital Project, Group 4

This project aims to prioritize patients in a hospital emergency room and assign seats to walk-ins. The program treats ambulance arrivals first and assigns seats to people who walk in by themselves for potential contact tracing. The seating area has 25 seats in a 5x5 pattern, and only seat neighbors within a row need tracking.


## Authors

- [@Favour R.](https://github.com/fav0u)
- [@Mohanad A.](https://github.com/ic22b110Mohanad)
- [@Philipp H.](https://github.com/philipphoertnagl)

## Compiling
When using the terminal (bash shell, zsh, etc.) go in the **build** directory and use the following commands:

`cmake ..`

then use the command:
`make all`

for deleting binary and executable files use:
`make clean`


If you use CLion or any other IDE which works with CMake just download the project and paste the folder in the IDE. Build the project and run it.
