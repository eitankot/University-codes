
/**
 * Triangle.java represents a triangle in the Euclidean space.
 *
 * @author RedScarf
 * @version 7.4.2021
 */
public class Triangle
{
    // instance variables 
    private Point _point1;
    private Point _point2;
    private Point _point3;
    static final double EPSILON = 0.001;

    /**
     * Construct a new Triangle (default constructor) from 3 default Points:(1,0),(-1,0),(0,1).
     */
    public Triangle()
    {
        _point1 = new Point(1,0);
        _point2 = new Point(-1,0);
        _point3 = new Point(0,1);
    }

    /**
     * Construct a new Triangle (from 3 points).
     * @param p1 the first Point
     * @param p2 the second Point
     * @param p3 the third Point
     */
    public Triangle(Point p1, Point p2, Point p3)
    {
        this();
        if (isValid(p1, p2, p3))
        {
            _point1 = new Point(p1);
            _point2 = new Point(p2);
            _point3 = new Point(p3);
        }

    }

    /**
     * Construct a new Triangle (from 6 reals).
     * @param x1 the x coordinate of the first Point
     * @param y1 the y coordinate of the first Point
     * @param x2 the x coordinate of the second Point
     * @param y2 the y coordinate of the second Point
     * @param x3 the x coordinate of the third Point
     * @param y3 the y coordinate of the third Point
     */
    public Triangle(double x1,double y1,double x2,double y2,double x3,double y3)
    {
        this();
        Point p1 = new Point(x1,y1);
        Point p2 = new Point(x2,y2);
        Point p3 = new Point(x3,y3);
        if (isValid(p1, p2, p3))
        {
            _point1 = new Point(p1);
            _point2 = new Point(p2);
            _point3 = new Point(p3);
        }

    }

    /**
     * Copy constructor Creates a new triangle identical to the given triangle
     * @param other the triangle to be copied
     */
    public Triangle(Triangle other)
    {
        _point1 = new Point(other._point1);
        _point2 = new Point(other._point2);
        _point3 = new Point(other._point3);
    }

    // getter and setters:
    /**
     * This method returns the triangle's first point.
     * @return The first point of the triangle
     */
    public Point getPoint1()
    {
        return new Point(_point1);
    }

    /**
     * This method returns the triangle's second point.
     * @return The second point of the triangle
     */
    public Point getPoint2()
    {
        return new Point(_point2);
    }

    /**
     * This method returns the triangle's third point.
     * @return The third point of the triangle
     */
    public Point getPoint3()
    {
        return new Point(_point3);
    }

    /**
     * This method sets the first point of the triangle.
     * @param p The new first point
     */
    public void setPoint1(Point p)
    {
        if (isValid(p, _point2, _point3))
            _point1 = new Point(p);
    }

    /**
     * This method sets the second point of the triangle.
     * @param p The new second point
     */
    public void setPoint2(Point p)
    {
        if (isValid(_point1, p, _point3))
            _point2 = new Point(p);
    }

    /**
     * This method sets the third point of the triangle.
     * @param The new third point
     */
    public void setPoint3(Point p)
    {
        if (isValid(_point1, _point2, p))
            _point3 = new Point(p);
    }

    /**
     * this method calculate the Epsilon and check if they are equal.
     * @param firstSide the first side to calculate
     * @param secondSidethe second side to calculate
     * @return true if they are under epsilon
     */
    private boolean calcEpsilon(double firstSide,double secondSide)
    {
        if (Math.abs(firstSide-secondSide) < EPSILON)
            return true;
        return false;
    }

    /**
     * This method checks if 3 points make a valid triangle.
     * @param p1 the first point
     * @param p2 the second point
     * @param p3 the third point
     * @return true if the triangle(p1,p2,p3) is valid
     */
    public boolean isValid(Point p1, Point p2, Point p3)
    {
        double firstSide = p1.distance(p2);
        double secondSide = p1.distance(p3);
        double thirdSide = p3.distance(p2);
        // check if its a vaild sides
        if (calcEpsilon(firstSide, (secondSide+thirdSide)) || calcEpsilon(secondSide, (firstSide+thirdSide)) || calcEpsilon(thirdSide, (secondSide+firstSide)))
            return false;
        if (firstSide >= (secondSide+thirdSide) || secondSide >= (firstSide+thirdSide) || thirdSide >= (firstSide+secondSide))
            return false;
        return true;
    }

    /**
     * This method returns a String representation of the Triangle. 
     * @return a String representation of the triangle
     */
    public String toString()
    {
        return ("{" + _point1 + "," + _point2 + ","+ _point3 +"}");
    }

    /**
     * This method returns the triangle's perimeter.
     * @return the triangle's perimeter
     */
    public double getPerimeter()
    {
        return (_point1.distance(_point2)+_point1.distance(_point3)+_point3.distance(_point2)); // get the perimeter
    }

    /**
     * This method returns the triangle's area (using Heron's formula).
     * @return the triangle's area
     */
    public double getArea()
    {
        double firstSide = _point1.distance(_point2);
        double secondSide = _point1.distance(_point3);
        double thirdSide = _point3.distance(_point2);
        return (0.25*Math.sqrt((firstSide+secondSide+thirdSide)*((-firstSide)+secondSide+thirdSide)*(firstSide-secondSide+thirdSide)*(firstSide+secondSide-thirdSide))); // the calculation of area
    }

    /**
     * This method returns true if the triangle is an isosceles triangle.
     * @return true if the triangle is an isosceles triangle
     */
    public boolean isIsosceles()
    {
        double firstSide = _point1.distance(_point2);
        double secondSide = _point1.distance(_point3);
        double thirdSide = _point3.distance(_point2);
        if (calcEpsilon(firstSide,secondSide) || calcEpsilon(firstSide,thirdSide) || calcEpsilon(secondSide,firstSide) || calcEpsilon(secondSide,thirdSide) || calcEpsilon(thirdSide,firstSide) || calcEpsilon(thirdSide,secondSide))
        {    
            return true;
        }
        return false;
    }

    /**
     * This method returns true if the triangle is a right-angled triangle.
     * @return true if the triangle is a right-angled triangle
     */
    public boolean isPythagorean()
    {
        double firstSide = _point1.distance(_point2);
        double secondSide = _point1.distance(_point3);
        double thirdSide = _point3.distance(_point2);
        if (secondSide < firstSide && thirdSide < firstSide) // check if the first side is the hypotenuse.
            if (calcEpsilon((firstSide*firstSide),((secondSide*secondSide)+(thirdSide*thirdSide))))// check if its Pythagorean
                return true;
        if (firstSide < secondSide && thirdSide < secondSide) // check if the second side is the hypotenuse.
            if (calcEpsilon((secondSide*secondSide) ,((firstSide*firstSide)+(thirdSide*thirdSide))))// check if its Pythagorean
                return true;
        if (firstSide < thirdSide && secondSide < thirdSide)// check if the third side is the hypotenuse.
            if (calcEpsilon((thirdSide*thirdSide) ,((firstSide*firstSide)+(secondSide*secondSide))))// check if its Pythagorean
                return true;
        return false;
    }

    /**
     * This method returns true if the triangle is in a given circle.
     * @param x the x value of the point which is the center of the circle
     * @param y the y value of the point which is the center of the circle
     * @param r the radius of the circle
     * @return true if the triangle is in a given circle.
     */
    public boolean isContainedInCircle(double x, double y, double r)
    {
        Point centerPoint = new Point(x,y);
        if (centerPoint.distance(_point1) < EPSILON+r && (centerPoint.distance(_point2) < EPSILON+r && centerPoint.distance(_point3) < EPSILON+r))// check if the distance is below the radius
            return true;
        return false;
    }

    /**
     * This method returns the lowest vertex of the triangle.
     * @return the lowest vertex
     */
    public Point lowestPoint()
    {
        Point lowestPoint; 
        if (_point1.isUnder(_point2))
            lowestPoint = _point1;
        else
        {
            if (_point2.isUnder(_point1))
                lowestPoint = _point2;
            else
            {
                if (_point2.isLeft(_point1))
                    lowestPoint = _point2;
                else
                    lowestPoint = _point1;
            }
        }
        if (_point3.isUnder(lowestPoint))
            lowestPoint = _point3;
        else
        {
            if (!(lowestPoint.isUnder(_point3)))
            {
                if (_point3.isLeft(lowestPoint))
                    lowestPoint = _point3;
            }
        }
        return new Point(lowestPoint);
    }

    /**
     * This method returns the highest vertex of the triangle.
     * @return the highest Vertex
     */
    public Point highestPoint()
    {
        Point highestPoint;
        if (_point1.isAbove(_point2))
            highestPoint = _point1;
        else
        {
            if (_point2.isAbove(_point1))
                highestPoint = _point2;

            else
            {
                if (_point2.isLeft(_point1))
                    highestPoint = _point2;
                else
                    highestPoint = _point1;
            }
        }
        if (_point3.isAbove(highestPoint))
            highestPoint = _point3;
        else
        {
            if (!(highestPoint.isAbove(_point3)))
            {
                if (_point3.isLeft(highestPoint))
                    highestPoint = _point3;
            }
        }
        return new Point(highestPoint);
    }

    /**
     * This method returns true if the triangle is entirely in one quadrant.
     * @return true if the triangle is entirely in one quadrant
     */
    public boolean isLocated()
    {
        if (_point1.quadrant() == _point2.quadrant() && _point1.quadrant() == _point3.quadrant()) // check if all of the point are in the same quadrant
            return true;
        return false;
    }

    /**
     * Check if this triangle is completely above a received triangle.
     * @param other the triangle to check if this triangle is above
     * @return true if this triangle is above the other triangle
     */
    public boolean isAbove(Triangle other)
    {
        // check if all of the points are above the other points
        if (_point1.isAbove(other._point1) && _point1.isAbove(other._point2) && _point1.isAbove(other._point3))
            if (_point2.isAbove(other._point1) && _point2.isAbove(other._point2) && _point2.isAbove(other._point3))
                if (_point3.isAbove(other._point1) && _point3.isAbove(other._point2) && _point3.isAbove(other._point3))
                    return true;
        return false;
    }

    /**
     * Check if this triangle is completely below a received triangle.
     * @param other the triangle to check if this triangle is below
     * @return true if this triangle is below the other triangle
     */
    public boolean isUnder(Triangle other)
    {
        return (other.isAbove(this));
    }

    /**
     * Check if the given triangle is equal to this triangle.
     * @param other the triangle we are checking equality with
     * @return true if the triangle other is equal to this triangle
     */
    public boolean equals(Triangle other)
    {
        if (_point1.equals(other._point1) && _point2.equals(other._point2) && _point3.equals(other._point3))// check if they are equals
            return true;
        return false;
    }

    /**
     * Check if the given triangle is congruent to this triangle.
     * @param other the triangle we are checking congruency with
     * @return true if the triangle other is congruent to this triangle
     */
    public boolean isCongruent(Triangle other)
    {
        double firstside = _point1.distance(_point2); // the first side of the triangle 
        double secondside = _point1.distance(_point3);// the second side of the triangle 
        double thirdside = _point3.distance(_point2);// the third side of the triangle 
        double otherfirstside = other._point1.distance(other._point2);// the first side of the other triangle 
        double othersecondside = other._point1.distance(other._point3);// the second side of the other triangle 
        double otherthirdside = other._point3.distance(other._point2);// the third side of the other triangle 
        if (calcEpsilon(firstside, otherfirstside) || calcEpsilon(firstside, othersecondside) || calcEpsilon(firstside, otherthirdside)) // check if there is a side that is the same for the first side.
            if (calcEpsilon(secondside, otherfirstside) || calcEpsilon(secondside, othersecondside) || calcEpsilon(secondside, otherthirdside))// check if there is a side that is the same for the second side.
                if (calcEpsilon(thirdside, otherfirstside) || calcEpsilon(thirdside, othersecondside) || calcEpsilon(thirdside, otherthirdside))// check if there is a side that is the same for the third side.
                    return true;
        return false;
    }
}