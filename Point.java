
/**
 * Point.java represents a 2-Dimensional point in the Euclidean space.
 *
 * @author RedScarf
 * @version 4.3.2021
 */
import java.lang.Math;

public class Point
{
    private double _x; // x cordinate
    private double _y; // y cordinate
    // constractors
    /**
     * Constructs a new Point.
     * @param x the x coordinate.
     * @param y the y coordinate.
     */
    public Point(double x, double y)
    {
        _x = x;
        _y = y;
    }

    /**
     * Copy constructor Creates a new Point identical to the given point.
     * @param other the Point to be copied.
     */
    public Point (Point other)
    {
        _x = other._x;
        _y = other._y;
    }

    // getters and setters
    /**
     * Returns the x coordinate
     * @return a double
     */
    public double getX()
    {
        return _x;
    }

    /**
     * Returns the y coordinate.
     * @return a double
     */
    public double getY()
    {
        return _y;
    }

    /**
     * This method sets the x coordinate of the point.
     * @param num The new x coordinate
     */
    public void setX(double num)
    {
        _x = num;
    }

    /**
     * This method sets the y coordinate of the point.
     * @param num The new y coordinate
     */
    public void setY(double num)
    {
        _y = num;
    }

    /**
     * Returns a string representation of this Point.
     * @return A string representation of a Point object
     */
    public String toString()
    {
        return ("("+ _x + "," + _y + ")");
    }

    /**
     * Return true iff the given point is equal to this point.
     * @param other The point we are checking equality with
     * @return true iff the point other equals this point
     */
    public boolean equals(Point other)
    {
        return (_x == other._x && _y == other._y);  
    }

    /**
     * Check if this point is above a received point.
     * @param other The point to check if this point is above
     * @return True if this point is above the other point
     */
    public boolean isAbove(Point other)
    {
        return (_y > other._y);
    }
    
    /**
     * Check if this point is below a received point.
     * @param other The point to check if this point is below
     * @return True if this point is below the other point
     */
    public boolean isUnder(Point other)
    {
        return other.isAbove(this);
    }
    
    /**
     * Check if this point is left of a received point.
     * @param other The point to check if this point is left of
     * @return True if this point is left of the other point
     */
    public boolean isLeft(Point other)
    {
        return (_x < other._x);
    }
    
    /**
     * Check if this point is right of a received point.
     * @param other The point to check if this point is right of
     * @return True if this point is right of the other point
     */
    public boolean isRight(Point other)
    {
        return other.isLeft(this);
    }
    
    /**
     * Check the distance between this point and a received point.
     * @param other The point to check the distance from
     * @return The distance between this point and a received point
     */
    public double distance(Point other)
    {
        // calculate the distance
        double powerX = Math.pow(_x-other._x, 2); // the power of X1+X2
        double powerY = Math.pow(_y-other._y, 2); // the power of Y1 +Y2
        return Math.sqrt(powerX + powerY);
    }
    
    /**
     * Return number of quadrant or 0 if the point is on an axis
     * @return an int representing the quadrant number
     */
    public int quadrant()
    {
        final int ZERO_POINT = 0;
        final int FIRST_QUADRANT = 1;
        final int SECOND_QUADRANT = 2;
        final int THIRD_QUADRANT = 3;
        final int FOUTH_QUADRANT = 4;
        // check what is the quadrant.
        if (_x == 0 && _y == 0)
            return ZERO_POINT;
        else if(_x > 0 && _y > 0)
            return FIRST_QUADRANT;
        else if(_x < 0 && _y > 0)
            return SECOND_QUADRANT;
        else if(_x < 0 && _y < 0)
            return THIRD_QUADRANT;
        return FOUTH_QUADRANT;
    }
} // end of Point
