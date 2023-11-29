
/**
 * This class is the answers for EX14.
 *
 * @author RedScarf
 * @version 29.5.2021
 */
public class Ex14
{
    /**
     * The time complexity is O(n) - because there is only one loop in the code.
     * And the memorial complexity O(1) - because there is no array that is created in the code.
     * This function checks what is the maximal drop in the array.
     * @param a the array
     * @return int of the maximal drop in the array
     */
    public static int maximalDrop (int [] a)
    {
        int maximalNumber = Integer.MIN_VALUE ;
        int minimalNumber = Integer.MAX_VALUE ;
        int maximalDropNumber = 0;
        for(int i=0; i<a.length; i++)// one loop so its O(n)
        {
            if(a[i] > maximalNumber) // check if the new number is above the highest before.
            {
                maximalNumber = a[i];
                minimalNumber = Integer.MAX_VALUE; // reset the minimal drop.
            }
            if(a[i] < minimalNumber && a[i] < maximalNumber)//check if the minimal number is above the new number
                minimalNumber = a[i];
            if (maximalNumber - minimalNumber > maximalDropNumber &&  minimalNumber != Integer.MAX_VALUE)// check if the new maximal is above the last maximal drop.
                maximalDropNumber = maximalNumber - minimalNumber;
        }
        return maximalDropNumber;
    }

    /**
     * The time complexity is O(n*Logn) - we move only n(by the col checker)+n*logn(by the row checker) and thats equals to n*logn.
     * And the memorial complexity O(1) - because there is no array that is created in the code.
     * This function checks if there is a sink in the array.
     * @param mat the array
     * @return int of the x axis number.
     */
    public static int isSink (int [][] mat)
    {
        int indexRow = 0;
        int i = 0;
        int lastZero = -1;
        while (i<mat.length && indexRow < mat.length) // check the row of the array
        {
            if(i == indexRow+1 && mat[indexRow][i] == 0)
                lastZero = i;
            if(mat[indexRow][i] == 1 || (indexRow == lastZero)) // check if its one and moves to the row under
            {
                lastZero = -1;
                indexRow += 1;
                i = 0;
            }
            else
                i++;
        }
        if (i == mat.length) // checks if there is a whole 0 line.
        {
            i = 0;
            int counter = 0;
            while (i<mat.length) // moves on the cols.
            {
                if(mat[i][indexRow] == 1) // check is the col is ok
                {
                    counter += 1;
                }
                i++;
            }
            if(counter == mat.length-1)// checks if its a sink
            {
                return indexRow;
            }
        }
        return -1;
    }

    /**
     * This class checks the size of a stain.
     * @param mat the array to use
     * @param x the x position of the stain
     * @param y the y position of the stain
     * @return int of the size of the stain
     */
    public static int size (boolean[][] mat, int x, int y)
    {
        boolean[][] tempmat = new boolean[mat.length][mat[0].length];
        return size(mat, tempmat, x, y, 0); // overloading
    }

    /**
     * This class checks the size of a stain.
     * @param mat the array to use
     * @param x the x position of the stain
     * @param y the y position of the stain
     * @param sum the sum of the stains in the position.
     * @return int of the size of the stain
     */
    private static int size (boolean[][] mat, boolean[][] tempmat, int x, int y, int sum)
    {
        if (x < 0 || y<0 || x >= mat.length || y>= mat[0].length)// check if the x,y are in the array
            return sum;
        if(mat[x][y] == false || tempmat[x][y] == true)// check if its a non selected stain and if its a stain.
            return sum;
        tempmat[x][y] = true;
        sum += 1;
        return sum + size(mat, tempmat, x+1, y, 0)+size(mat, tempmat, x, y+1, 0)+size(mat, tempmat, x+1, y+1, 0)+size(mat, tempmat, x+1, y-1, 0)+size(mat, tempmat, x-1, y+1, 0)+size(mat, tempmat, x-1, y-1, 0)+size(mat, tempmat, x-1, y, 0)+size(mat, tempmat, x, y-1, 0); // rec
    }

    /**
     * This class checks if the two arrays are permutation.
     * @param a the first array to check if its permutation
     * @param b the second array to check if its permutation
     * @return true if they are permutation
     */
    public static boolean isPermutation (int [] a, int [] b)
    {
        return isPermutation (a, b, 0, 0,0); // overloading
    }

    /**
     * This class checks if the two arrays are permutation.
     * @param a the first array to check if its permutation
     * @param b the second array to check if its permutation
     * @param indexA The index in the array A
     * @param indexB The index in the array B
     * @param count the count to check if the two list are equals. 
     * @return true if they are permutation
     */
    private static boolean isPermutation (int [] a, int [] b, int indexA, int indexB, int count)
    {
        if(a.length != b.length)
            return false;
        if(indexB == b.length) // check if the b index are under the length
        {
            indexA += 1;
            indexB = 0;
        }
        if (count == a.length && indexA == a.length) // // check if the b index in the length and the count is equals to the length
        {
            return true;
        }
        if (indexA == a.length) // check if the a index are under the length
            return false;
        int numhold = b[indexB];
        boolean isTrue;
        if(a[indexA] == b[indexB]) // check if the two numbers are equals
        {
            b[indexB] = Integer.MAX_VALUE;
            count += 1;
            isTrue = isPermutation(a, b, indexA+1, 0, count); // rec
            b[indexB] = numhold;
        }
        else
        {
            isTrue = isPermutation(a, b, indexA, indexB+= 1, count); // rec
        }
        return isTrue;
    }
}
