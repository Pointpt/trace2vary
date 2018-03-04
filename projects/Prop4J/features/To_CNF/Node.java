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
	
	
	
	@SuppressWarnings("unchecked")
	public Node toCNF() {
		Node node = this;
		node = node.eliminate(Choose.class, Equals.class, Implies.class);
		node = node.eliminate(Not.class);
		node = node.eliminate(AtMost.class, AtLeast.class);
		node = node.eliminate(Not.class);
		node = node.clausify();
		return node;
	}

	@SuppressWarnings("unchecked")
	public Node toCNFprintln() {
		Node node = this;
		System.out.println(node);
		node = node.eliminate(Choose.class, Equals.class, Implies.class);
		System.out.println(node);
		node = node.eliminate(Not.class);
		System.out.println(node);
		node = node.eliminate(AtMost.class, AtLeast.class);
		System.out.println(node);
		node = node.eliminate(Not.class);
		System.out.println(node);
		node = node.clausify();
		System.out.println(node);
		System.out.println();
		return node;
	}
	

}