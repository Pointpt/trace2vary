package GPL; import java.util.Iterator;
import java.util.LinkedList;
public  class Vertex implements EdgeIfc, NeighborIfc {
	public /*@ spec_public @*/ LinkedList adjacentVertices;

	public /*@ spec_public @*/ String name;



	public Vertex() {
        VertexConstructor();
    }

	/*@ ensures name == null && adjacentVertices != null; @*/

	private void VertexConstructor__wrappee__Number  () {
        name      = null;
        adjacentVertices = new LinkedList();
    }

	/*@ ensures \original && visited == false; @*/

	private void VertexConstructor__wrappee__BFS  ( ) 
    {
        VertexConstructor__wrappee__Number();
        visited = false;
    }

	/*@ requires \original; 
	 ensures \original; 
	 ensures weightsList!=null; @*/

	public void VertexConstructor() {
        VertexConstructor__wrappee__BFS();
        weightsList = new LinkedList();
    }

	/*@ requires name != null;
    ensures this.name == name;
    ensures \result == this; @*/

	public  Vertex assignName( String name ) {
        this.name = name;
        return ( Vertex ) this;
    }

	/*@ ensures \result == this.name; @*/

	public /*@pure@*/ String getName( ) 
    { 
        return name; 
    }

	/*@ requires n != null;
    ensures adjacentVertices.getLast()==n; @*/

	public void addAdjacent( Vertex n ) {
        adjacentVertices.add( n );
    }



	private void adjustAdorns__wrappee__BFS  ( Vertex the_vertex, int index ) 
      {}

	/*@ requires \original && the_vertex != null;
    ensures \original && weightsList.getLast() == the_vertex.weightsList.get(index).intValue(); @*/

	public void adjustAdorns( Vertex the_vertex, int index )
    {
        int the_weight = ( ( Integer )the_vertex.weightsList.get( index ) ).intValue();
        weightsList.add( new Integer( the_weight ) );
        adjustAdorns__wrappee__BFS( the_vertex, index );
    }



	public VertexIter getNeighbors( ) 
    {
        return new VertexIter( ) 
        {
            private Iterator iter = adjacentVertices.iterator( );
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



	private void display__wrappee__TestProg  () {
        int s = adjacentVertices.size();
        int i;

        System.out.print( "Vertex " + name + " connected to: " );

        for ( i=0; i<s; i++ )
            System.out.print( ( ( Vertex )adjacentVertices.get( i ) ).name+", " );
        System.out.println();
    }



	private void display__wrappee__Number  ( ) 
    {
        System.out.print( " # "+ VertexNumber + " " );
        display__wrappee__TestProg( );
    }



	private void display__wrappee__BFS  ( ) 
    {
        if ( visited )
            System.out.print( "  visited " );
        else
            System.out.println( " !visited " );
        display__wrappee__Number( );
    }



	public void display()
    {
        int s = weightsList.size();
        int i;

        System.out.print( " Weights : " );

        for ( i=0; i<s; i++ ) {
            System.out.print( ( ( Integer )weightsList.get( i ) ).intValue() + ", " );
        }

        display__wrappee__BFS();
    }



	public Vertex getStart( ) { return null; }



	public Vertex getEnd( ) { return null; }



	public void setWeight( int weight ){}



	public /*@pure@*/  int getWeight() { return 0; }



	public /*@pure@*/  Vertex getOtherVertex( Vertex vertex )
    {
        return this;
    }



	public void adjustAdorns( EdgeIfc the_edge )
    {
    }

	public  /*@ spec_public @*/ int  VertexNumber;

	public /*@ spec_public @*/ boolean visited;

	/*@ requires w != null; @*/

	public void init_vertex( WorkSpace w ) 
    {
        visited = false;
        w.init_vertex( ( Vertex ) this );
    }



	public void nodeSearch( WorkSpace w ) 
    {
        int     s, c;
        Vertex  v;
        Vertex  header;

        // Step 1: if preVisitAction is true or if we've already
        //         visited this node
        w.preVisitAction( ( Vertex ) this );

        if ( visited )
        {
            return;
        }

        // Step 2: Mark as visited, put the unvisited neighbors in the queue
        //     and make the recursive call on the first element of the queue
        //     if there is such if not you are done
        visited = true;

        // Step 3: do postVisitAction now, you are no longer going through the
        // node again, mark it as black
        w.postVisitAction( ( Vertex ) this );

        // enqueues the vertices not visited
        for ( VertexIter vxiter = getNeighbors( ); vxiter.hasNext( ); )
        {
            v = vxiter.next( );

            // if your neighbor has not been visited then enqueue
            if ( !v.visited ) 
            {
                GlobalVarsWrapper.Queue.add( v );
            }

        } // end of for

        // while there is something in the queue
        while( GlobalVarsWrapper.Queue.size( )!= 0 )
        {
            header = ( Vertex ) GlobalVarsWrapper.Queue.get( 0 );
            GlobalVarsWrapper.Queue.remove( 0 );
            header.nodeSearch( w );
        }
    }

	public /*@ spec_public @*/ LinkedList weightsList;

	/*@ ensures weightsList.getLast().intValue()==weight; @*/

	public void addWeight( int weight )
    {
        weightsList.add( new Integer( weight ) );
    }


}
