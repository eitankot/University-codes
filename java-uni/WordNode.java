
/**
 * This class is a node that represents a data base for words.
 *
 * @author RedScarf
 * @version 11.6.2021
 */
public class WordNode
{
    private String _word;
    private WordNode _next;

    /**
     * constructor the time complexity is O(1) because we don't run on only one loop. And the memory complexity is O(1) because we are not creating any arrays.
     * this is the constactor of WordNode
     * @param word the value of the word to be in the node
     * @param next the next node.
     */
    public WordNode(String word, WordNode next)
    {
       _word = word;
       _next = next;
    }
    
    /**
     * constructor the time complexity is O(1) because we don't run on only one loop. And the memory complexity is O(1) because we are not creating any arrays.
     * this is the constactor of WordNode
     */
    public WordNode()
    {
       _word = null;
       _next = null;
    }
    
    /**
     * constructor the time complexity is O(1) because we don't run on only one loop. And the memory complexity is O(1) because we are not creating any arrays.
     * the getter of the value
     * @return a string that represents the word.
     */
    public String getValue()
    {
        return _word;
    }
    
    /**
     * constructor the time complexity is O(1) because we don't run on only one loop. And the memory complexity is O(1) because we are not creating any arrays.
     * the getter of the next node
     * @return a WordNode that represents the next node.
     */
    public WordNode getNext()
    {
        return _next;
    }
    
    /**
     * constructor the time complexity is O(1) because we don't run on only one loop. And the memory complexity is O(1) because we are not creating any arrays.
     * the setter of the value.
     * @param word the word to change
     */
    public void setValue(String word)
    {
        _word = word;
    }
    
    /**
     * constructor the time complexity is O(1) because we don't run on only one loop. And the memory complexity is O(1) because we are not creating any arrays.
     * the setter of the next node.
     * @param next the next node to change
     */
    public void setNext(WordNode next)
    {
        _next = next;
    }
    
    /**
     * constructor the time complexity is O(1) because we don't run on only one loop. And the memory complexity is O(1) because we are not creating any arrays.
     * an override to toString.
     * @return a string that represent the word.
     */
    public String toString()
    {
        return _word;
    }
}