# ClimaVisionArtificial
On the build directory, you'll find two directories. I had one more, "fotosVision" that has the photos taken by me for the inicial test. I couldn't upload that because of the size.

Those photos were processed with the program "sun.cxx". It makes a histogram per photo with the percentage of pixels per intensity for the blue channel. I've classified each histogram in two directories, rain and notrain depending on if it was rainnig when I took the photo.

If you want to add an histogram of one photo, you can run the "addPhoto.cxx" program and it will give you a histogram and it depends on you to put it in the directory (rain or not rain).

If you want to see the results on a image, run the "testImage.cxx" program it will print the raining percentage seen on that image by two methods.
