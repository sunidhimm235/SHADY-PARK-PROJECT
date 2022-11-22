# SHADY PARK PROJECT
According to the length of the park, the location and height of vertical towers that can block sunlight, and the percentage of the park that must be shaded, the program determines the beginning and ending angles of the sun that cause the park to be too sunny.

Input will occur on a line consisting of 3 integers, N, L, and P (2 ≤ N ≤ 500,000; 1 ≤ L ≤ 1,000,000,000; 1 ≤ P ≤ 100), which indicate the number of sun-blocking towers, the park's length, and shade coverage percentage. A sun-blocking tower description will be presented on each of the next N lines.

The sun-blocking tower information will include a set of 2 space-separated integers, x and h (0 ≤ x ≤ L; 1 ≤ h ≤ 1,000,000,000), representing the location from the westernmost point of the park and the height of the tower respectively. The towers will be arranged in increasing order of their location. The locations of the towers will not be the same. Location 0, and location L, will always be the location of the first tower and the last tower, respectively.

The output will contain two space separated floating point values, S and E, representing the beginning and ending angles of the sun from the eastern horizon in degrees, respectively. To ensure accuracy, both values are rounded to exactly five decimal places.
