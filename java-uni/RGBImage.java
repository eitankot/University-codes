/**
 * RGBImage represents an image by two dimensional arrays.
 *
 * @author RedScarf
 * @24.4.2021
 */
public class RGBImage
{
    private RGBColor[][] _image;

    /**
     * Construct a black array of RGBImage
     * @param rows the number of rows
     * @param cols the number of coloumns
     */
    public RGBImage(int rows, int cols)
    {
        _image = new RGBColor[rows][cols];
        for(int i=0; i<rows; i++)
            for(int j=0; j < cols; j++)
            {
                _image[i][j] = new RGBColor();
            }   
    }

    /**
     * Construct an image by the givan array of pixels.
     * @param pixels the array to copy the pixels from
     */
    public RGBImage(RGBColor[][] pixels)
    {
        _image = new RGBColor[pixels.length][pixels[0].length];
        for(int i=0; i<_image.length; i++)
            for(int j=0; j < _image[0].length; j++)
            {
                _image[i][j] = new RGBColor(pixels[i][j]);
            }   
    }

    /**
     * Construct an image by the givan the other RGBImage of pixels.
     * @param other the other RGBImage to copy the pixels from
     */
    public RGBImage(RGBImage other)
    {
        _image = new RGBColor[other._image.length][other._image[0].length];
        for(int i=0; i<_image.length; i++)
            for(int j=0; j < _image[0].length; j++)
            {
                _image[i][j] = new RGBColor(other._image[i][j]);
            }
    }

    // setters and getters
    /**
     * return the width of the array.
     * @return the width by int
     */
    public int getWidth()
    {
        return _image[0].length;
    }

    /**
     * return the height of the array.
     * @return the height by int
     */
    public int getHeight()
    {
        return _image.length;
    }

    /**
     * return the specific pixel that requested.
     * @param row the index of the row of the pixel
     * @param col the index of the coloumn
     * @return the pixel that requested
     */ 
    public RGBColor getPixel(int row, int col)
    {
        if (row <= _image.length-1 && col <= _image[0].length-1) 
            return new RGBColor(_image[row][col]);
        return new RGBColor();
    }

    /**
     * set the specific pixel by using RGBColor to change the colors.
     * @param row the index of the row of the pixel
     * @param col the index of the coloumn
     * @param pixel the RGBColor to change
     */
    public void setPixel(int row, int col, RGBColor pixel)
    {
        if (row <= _image.length-1 && col <= _image[0].length-1)
            _image[row][col] = new RGBColor(pixel);
    }

    /**
     * check if the two arrays are equals.
     * @param other the other RGBImage to check
     * @reutrn true iff they are equals
     */
    public boolean equals(RGBImage other)
    {
        if (other._image.length == _image.length && other._image[0].length == _image[0].length) // check if the length are equals
        {
            for(int i=0; i<_image.length; i++) // check if the all the pixals are equal
                for(int j=0; j<_image[i].length; j++)
                    if (!(_image[i][j].equals(other._image[i][j])))
                        return false;
            return true;
        }
        return false;
    }

    /**
     * flip the image vertical axis.
     */
    public void flipVertical()
    {
        for(int i=0 ; i<_image.length/2; i++) // does the flipVertical
        {
            RGBColor tmpImage[][] = new RGBColor[_image.length][_image[i].length]; 
            tmpImage[i] = _image[_image.length-i-1];
            _image[_image.length-i-1] = _image[i];
            _image[i] = tmpImage[i];
        }
    }

    /**
     * flip the image horizontal axis.
     */
    public void flipHorizontal()
    {
        for(int j=0; j<_image[0].length/2; j++) // does the flipHorizontal
        {
            RGBColor tmpImage[][] = new RGBColor[_image.length][_image[0].length];
            for(int i=0 ; i<_image.length; i++)
            {
                tmpImage[i][j] = _image[i][_image[i].length-j-1];
                _image[i][_image[i].length-j-1] = _image[i][j];
                _image[i][j] = tmpImage[i][j];
            }
        }
    }

    /**
     * Inverts the color of the array by using RGBColor, by replacing in the array each component value with its complement relative to 255.
     */
    public void invertColors()
    {
        for(int i=0; i<_image.length; i++) // invert the color
            for(int j=0; j<_image[i].length; j++)
            {
                _image[i][j].invert();
            }
    }

    /**
     * rotate the image by 90 degrees to the clockwise position.
     */
    public void rotateClockwise()
    {
        RGBColor tmpImage[][] = new RGBColor[_image[0].length][_image.length];
        for(int i=0; i < _image.length; i++)
            for(int j=0; j < _image[0].length; j++)
            {
                tmpImage[j][i] = _image[_image.length-i-1][j];
            }
        _image = tmpImage;
    }

    /**
     * rotate the image by 90 degrees to the counter clockwise position.
     */
    public void rotateCounterClockwise()
    {
        RGBColor tmpImage[][] = new RGBColor[_image[0].length][_image.length];
        for(int i=0; i < _image.length; i++)
            for(int j=0; j < _image[0].length; j++)
            {
                tmpImage[j][i] = _image[i][_image[0].length-j-1];
            }
        _image = tmpImage;
    }

    /**
     * shifts the coloumns by the given amount and turn the shifted coloumns into black pixels.
     * @param offset the amount to shift the coloumn
     */
    public void shiftCol(int offset)
    {
        RGBColor tmpImage[][] = new RGBColor[_image.length][_image[0].length];
        if(_image[0].length >= Math.abs(offset))
            if(offset >= 0)
            {
                for(int i=0 ; i<_image.length; i++)
                {
                    for(int j=0 ; j<_image[0].length-Math.abs(offset); j++)
                    {
                        tmpImage[i][j+Math.abs(offset)] = _image[i][j];

                    }
                    for(int tmpOffset = 0; tmpOffset < Math.abs(offset); tmpOffset++)
                        tmpImage[i][tmpOffset] = new RGBColor();
                }
                _image = tmpImage;
            }
            else
            {
                for(int i=0 ; i<_image.length; i++)
                {
                    for(int j=_image[i].length-1 ; j>Math.abs(offset)-1; j--)
                    {
                        tmpImage[i][j-Math.abs(offset)] = _image[i][j];
                    }
                    for(int tmpOffset = _image[i].length-1; tmpOffset > _image[i].length-1-Math.abs(offset); tmpOffset--)
                        tmpImage[i][tmpOffset] = new RGBColor();
                }
                _image = tmpImage;
            }
    }

    /**
     * shifts the rows by the given amount and turn the shifted rows into black pixels.
     * @param offset the amount to shift the row
     */
    public void shiftRow(int offset)
    {
        RGBColor tmpImage[][] = new RGBColor[_image.length][_image[0].length];
        if(_image[0].length >= Math.abs(offset))
            if(offset >= 0)
            {
                for(int i=0 ; i<_image.length-offset; i++)
                {
                    tmpImage[i+offset] = _image[i];
                } 
                for(int tmpOffset = 0; tmpOffset < Math.abs(offset); tmpOffset++)
                    for(int j=0; j<_image[0].length; j++)
                        tmpImage[tmpOffset][j] = new RGBColor();
                _image = tmpImage;
            }
            else
            {
                for(int i=_image.length-1 ; i>=Math.abs(offset); i--)
                {
                    tmpImage[i-Math.abs(offset)] = _image[i];
                }
                for(int tmpOffset = _image.length-1; tmpOffset >= _image.length-Math.abs(offset); tmpOffset--)
                    for(int j=0; j<_image[0].length; j++)
                        tmpImage[tmpOffset][j] = new RGBColor();
                _image = tmpImage;
            }
    }

    /**
     * Returns the grayscale value for the whole array, by using the RGBColor method.
     * @return an double array of the calculated gray scale array. 
     */
    public double[][] toGrayscaleArray()
    {
        double tmpImage[][] = new double[_image.length][_image[0].length];
        for(int i=0; i<_image.length; i++)
            for(int j=0; j<_image[i].length; j++)
            {
                tmpImage[i][j] = _image[i][j].convertToGrayscale();
            }
        return tmpImage;
    }

    /**
     * Returns a string representation of this RGB triplet array.
     * @return string representation of this RGB triplet array
     */
    public String toString()
    {
        String str = "";
        for(int i = 0; i<_image.length; i++)
        {
            for(int j = 0; j<_image[0].length; j++)
                str += _image[i][j];
            str += "\n";
        }
        return str;
    }

    /**
     * return a copy of the image/array.
     * @return copy of the array
     */
    public RGBColor[][] toRGBColorArray()
    {
        RGBImage other = new RGBImage(_image);
        return other._image;
    }
}
