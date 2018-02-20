package GPL; import java.util.Iterator;
import java.util.LinkedList;
import java.util.Comparator;
import java.util.Collections;
public  class Graph {
	public  /*@ spec_public @*/   LinkedList vertices;

	public /*@ spec_public @*/ static final boolean isDirected = true;



	public Graph() {
        vertices = new LinkedList();
    }

	/*@ ensures \result != null; @*/

	public VertexIter getVertices( ) 
    { 
        // dja - trying to fix logic problems
        return new VertexIter( ) 
        {
                private Iterator iter = vertices.iterator( );
                public Vertex next( ) 
                { 
                    return ( Vertex )iter.next( ); 
                }
                public boolean hasNext( ) 
                { 
                    return iter.hasNext( ); 
                }
            };

    }



	private void run__wrappee__TestProg  ( Vertex s ) {}



	public void run( Vertex s )
     {
       	System.out.println("Number");
        NumberVertices( );
        run__wrappee__TestProg( s );
    }



	/*@public model pure boolean isSorted(LinkedList list) {
 	return true;
 	}@*/

	/*@ requires c != null;
    ensures isSorted(vertices); @*/

	public void sortVertices(Comparator c) {
        Collections.sort(vertices, c);
    }

	/*@ requires start != null && end != null && weight != null;
	ensures findsEdge(start,end) != null && findsEdge(start, end).getWeight()==weight; @*/

	public void addAnEdge  ( Vertex start,  Vertex end, int weight )
   {
        addEdge( start,end, weight );
    }

	/*@ requires v != null;
    ensures vertices.getLast()==v; @*/

	public void addVertex( Vertex v ) {
        vertices.add( v );
    }

	/*@ requires v1 != null && v2 != null; 
	 ensures \result.getOtherVertex(v1)==v2 && \result.getOtherVertex(v2)==v1; @*/

	public EdgeIfc addEdge( Vertex start,  Vertex end ) {
        start.addAdjacent( end );
        return( EdgeIfc ) start;
    }

	/*@ ensures (theName == null) ==> (\result == null); 
     ensures (\forall int i; i >= 0 && i < vertices.size; (vertices.get(i)!=null) ==> (vertices.get(i).getName().equals(theName) ==> \result != null)); 
     ensures (\result != null) ==> \result.getName() == theName; @*/

	public /*@pure@*/ Vertex findsVertex( String theName )
      {
        int i=0;
        Vertex theVertex;

        // if we are dealing with the root
        if ( theName==null )
            return null;

        for( i=0; i<vertices.size(); i++ )
            {
            theVertex = ( Vertex )vertices.get( i );
            if ( theName.equals( theVertex.name ) )
                return theVertex;
        }
        return null;
    }



	private void display__wrappee__BFS  () {
        int s = vertices.size();
        int i;

        System.out.println( "******************************************" );
        System.out.println( "Vertices " );
        for ( i=0; i<s; i++ )
            ( ( Vertex ) vertices.get( i ) ).display();
        System.out.println( "******************************************" );

    }



	public void display() 
   {
        display__wrappee__BFS();
    }



	public void NumberVertices( ) 
    {
        GraphSearch( new NumberWorkSpace( ) );
    }



	public void GraphSearch( WorkSpace w ) 
    {
        // Step 1: initialize visited member of all nodes
        VertexIter vxiter = getVertices( );
        if ( vxiter.hasNext( ) == false )
        {
            return;
        }

        // Showing the initialization process
        while(vxiter.hasNext( ) ) 
        {
            Vertex v = vxiter.next( );
            v.init_vertex( w );
        }

        // Step 2: traverse neighbors of each node
        for (vxiter = getVertices( ); vxiter.hasNext( ); ) 
        {
            Vertex v = vxiter.next( );
            if ( !v.visited ) 
            {
                w.nextRegionAction( v );
                v.nodeSearch( w );
            }
        } //end for
    }

	/*@ requires start != null && end != null ;
	 ensures \result.getOtherVertex(start)==end && \result.getOtherVertex(end)==start; 
    ensures !isDirected ==> (theNeighbor.neighbor.getWeight()==theNeighbor.weight); @*/

	public void addEdge( Vertex start,  Vertex end, int weight )
   {
        addEdge( start,end ); // adds the start and end as adjacent
        start.addWeight( weight ); // the direction layer takes care of that
                
        // if the graph is undirected you have to include 
        // the weight of the edge coming back
        if ( isDirected==false )
            end.addWeight( weight );
    }


}
