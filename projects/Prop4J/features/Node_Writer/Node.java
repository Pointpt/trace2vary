import java.util.Arrays;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

/**
 * A propositional node that can be transformed into conjunctive normal form
 * (cnf).
 * 
 * @author Thomas Th�m
 */
public abstract class Node {
	
	@Override
	public String toString() {
		return NodeWriter.nodeToString(this);
	}

	/**
	 * Returns a string representation of this node. The symbols for logical
	 * connectors, e.g. And, are given as a parameter.
	 * 
	 * @see org.prop4j.NodeWriter.shortSymbols (default)
	 * @see org.prop4j.NodeWriter.logicalSymbols
	 * @see org.prop4j.NodeWriter.textualSymbols
	 * 
	 * @param  symbols  the symbols for logical connectors
	 * 
	 * @return a string representing this node
	 */
	public String toString(String[] symbols) {
		return NodeWriter.nodeToString(this, symbols);
	}

}