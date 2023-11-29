
/**
 * This class is a linked list that represents a data base for words.
 *
 * @author RedScarf
 * @version 11.6.2021
 */
public class TextList
{
    private WordNode _head;

    /**
     * reset constructor the time complexity is O(1) because we don't run any loops, and the memory complexity is O(1) because we are not creating any arrays during this code.
     * creates a empty linked list.
     */
    public TextList()
    {
        _head = null;
    }

    /**
     * constructor the time complexity is O(nlogn) because we use mergesort and the splitspaces is O(n) because we run on only one loop. And the memory complexity is consitent (thats how tamar called it in the video (11.5)).
     * this is the constactor of TextList
     * @param text the text to convernt into a linked list
     */
    public TextList(String text)
    {  
        if(!(text.equals("")|| text.equals("")))
        {
            _head = new WordNode();
            WordNode temp = _head;
            splitSpaces(text, temp);
            _head = mergeSort(_head);
        }
        else
        {
            _head = null;
        }
    }

    /**
     * the time complexity is O(n) because we run only on one loop, and the memory complexity is O(1) because we are not creating any arrays during this code.
     * this function adds a word to the linked list. 
     * @param word the word to add to the linked list.
     */
    public void addToData(String word)
    {
        WordNode tmpNode = new WordNode(word, null);
        WordNode cur = _head;
        WordNode prev = _head;
        if (!(word.equals("")))
        {
            if (_head != null)
            {
                while (cur != null)
                {
                    if (cur.getValue().compareTo(word) >= 0) // check if its the place to set the data.
                    {
                        tmpNode.setNext(cur);
                        if(cur == _head)
                            _head = tmpNode;
                        else
                            prev.setNext(tmpNode);
                        break;
                    }
                    prev = cur;
                    cur = cur.getNext();
                } 
                if( cur == null) // check if the item need to be in the last.
                    prev.setNext(tmpNode);
            }
            else
            {
                _head = tmpNode;
            }
        }
    }

    /**
     * the time complexity is O(n) because we run only on one loop, and the memory complexity is O(1) because we are not creating any arrays during this code.
     * this function count how many words are in the linked list.
     * @return the count of words in the list.
     */
    public int howManyWords()
    {
        int count = 0;
        WordNode cur = _head;
        if(_head != null)
        {
            while(cur != null)
            {
                count += 1;
                cur = cur.getNext();
            }
        }
        return count;
    }

    /**
     * the time complexity is O(n) because we run only on one loop, and the memory complexity is O(1) because we are not creating any arrays during this code.
     * this function count how many unique words are in the linked list.
     * @return the count of unique words in the list.
     */
    public int howManyDifferentWords ()
    {
        int count = 0;
        WordNode cur = _head;
        WordNode prev = null;
        if(_head != null)
        {
            count = 1;
            while(cur != null)
            {   
                if (prev != null)
                {
                    if (!(cur.getValue().equals(prev.getValue()))) // check if they are not equals
                    {
                        count += 1;
                    }
                }
                prev = cur;
                cur = cur.getNext();
            }

        }
        return count;
    }

    /**
     * the time complexity is O(n) because we run only on one loop, and the memory complexity is O(1) because we are not creating any arrays during this code.
     * this function check that is the most frequent word in the list.
     * @return a string of the most frequent word.
     */
    public String mostFrequentWord ()
    {
        int highestCount = 0;
        int count = 1;
        String hightWordFrequens = "";
        WordNode next = _head;
        WordNode cur = null;
        WordNode prev = null;
        if(_head != null)
        {
            while(next != null)
            {
                if (cur != null)
                {
                    if((cur.getValue().equals(next.getValue())))// check if they are equals and valid
                    {
                        count += 1;
                    }
                    else
                    {
                        count = 1;
                    }
                }
                if(count > highestCount)// check the count
                {
                    highestCount = count;
                    hightWordFrequens = next.getValue();
                }
                prev = cur;
                cur = next;
                next = cur.getNext();

            }
            if(prev != null && prev.getValue().equals(cur.getValue())) // check if they are equals and valid
                count += 1;
            else
                count = 1;
            if(count > highestCount)// check the count
            {
                highestCount = count;
                hightWordFrequens = cur.getValue();
            }
        }
        return hightWordFrequens;
    }

    /**
     * the time complexity is O(n) because we run only on one loop, and the memory complexity is O(1) because we are not creating any arrays during this code.
     * this function check how many staring words with the selected char.
     * @param letter the letter to check how many it starts with in the lincked list.
     * @return a int that represents how many time the letter was the first char in the linked list.
     */
    public int howManyStarting (char letter)
    {
        int count = 0;
        WordNode cur = _head;
        if(_head != null)
        {
            while(cur != null)
            {
                if(cur.getValue().charAt(0) == letter) // check if its the same letter
                    count += 1;
                cur = cur.getNext();
            }
        }
        return count;
    }

    /**
     * this function check what is the most frequent starting letter in the linked list.
     */
    public char mostFrequentStartingLetter()
    {
        if (_head == null) //  Stop conditions
            return ' ';
        return mostFrequentStartingLetter(_head, null ,0, -1 ,null); // overloading
    }

    /**
     * this function check what is the most frequent starting letter in the linked list.
     * this is a overloading of the function.
     * @param cur the current place in the linkedlist.
     * @param prev the previous place in the linkedlist.
     * @param count the count of the word.
     * @param highestCount the highest count that was in the linkedlist.
     * @param highestValue the WordNode of the most frequent letter.
     * @return a chat that represents the starting the most starting letter.
     */
    private char mostFrequentStartingLetter(WordNode cur,WordNode prev ,int count,int highestCount,WordNode highestValue)
    {
        if (cur == null) //  Stop conditions
            return highestValue.getValue().charAt(0);
        if (prev != null) //  step
            if(cur.getValue().charAt(0) == prev.getValue().charAt(0))// check if the chars are equals.
                count += 1;
            else
                count = 1;
        else
            count = 1;
        if (count > highestCount) // check if the count is the highest that was shown until now.
        {
            highestCount = count;
            highestValue = cur;
        }
        return mostFrequentStartingLetter(cur.getNext(), cur, count, highestCount, highestValue);
    }

    /**
     * the time complexity is O(n) because we run only on one loop, and the memory complexity is O(1) because we are not creating any arrays during this code.
     * this is the toString of the class.
     * @return a string that represent all of the words in the linked list.
     */
    public String toString()
    {
        WordNode cur = _head;
        String str = "";
        WordNode prev = null;
        int count = 1;
        if (_head != null)
        {
            while(cur != null)
            {   
                if (prev != null)
                {
                    if (cur.getValue().equals(prev.getValue()))
                    {
                        count += 1;
                    }
                    else
                    {
                        str += prev.getValue() + "\t" + count + "\n"; // add to the string
                        count = 1;
                    }
                }
                prev = cur;
                cur = cur.getNext();
            }
            str += prev.getValue() + "\t" + count + "\n";
        }
        return str;
    }

    /**
     * the time complexity is O(n) because we run only on one loop,And the memory complexity is consitent (thats how tamar called it in the video (11.5)).
     * this function split the spaces and creates a linked list.
     * @param text the text to split the spaces
     * @param node the node to use as the head of the linked list
     */
    private void splitSpaces(String text, WordNode node)
    {
        String tmpString = "";
        for(int i=0; i < text.length(); i++)
        {
            if (text.charAt(i) == ' ') // splits the list.
            {
                if( node.getNext() == null && i != text.length()-1) // check if its the last item in the list
                    node.setNext(new WordNode());
                node.setValue(tmpString);
                node = node.getNext();
                tmpString = "";
            }
            else
            {
                tmpString += text.charAt(i);
                if (i == (text.length()-1))
                {
                    node.setValue(tmpString);
                    node = node.getNext();
                    tmpString = "";
                }
            }
        }  
    }

    /**
     * the time complexity is O(n) because we run only on one loop,And the memory complexity is consitent (thats how tamar called it in the video (11.5)).
     * this class splits the list into two lists.
     * @param node the node to use
     */
    private WordNode split(WordNode node)
    {
        if (node == null || node.getNext() == null) //  Stop conditions
            return null;

        WordNode list2 = node.getNext();
        node.setNext(list2.getNext());
        list2.setNext(split(list2.getNext()));

        return list2;
    }

    /**
     * the time complexity is O(n) because we run only on one loop,And the memory complexity is consitent (thats how tamar called it in the video (11.5)).
     * this class merges the list.
     * @param list1 the first list to merge
     * @param list2 the second list to merge
     */
    private WordNode merge(WordNode list1, WordNode list2)
    {
        if (list1 == null) // Stop conditions
            return list2;
        if (list2 == null) // Stop conditions
            return list1;

        if (list1.getValue().compareTo(list2.getValue()) <= 0) // the step
        {
            list1.setNext(merge(list1.getNext(), list2));
            return list1;
        }
        else
        {
            list2.setNext(merge(list1, list2.getNext()));
            return list2;
        }
    }

    /**
     * the time complexity is O(nlogn) because we run only on one loop,And the memory complexity is consitent (thats how tamar called it in the video (11.5)).
     * this class is a merge sort.
     * @param node the node to use.
     */
    private WordNode mergeSort(WordNode node)
    {
        if(node == null || node.getNext() == null)// Stop conditions
            return node;

        WordNode list2 = split(node);

        node = mergeSort(node);
        list2 = mergeSort(list2);

        return merge(node, list2);
    }
}
