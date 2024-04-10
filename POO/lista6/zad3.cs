using System;

public abstract class Tree {
}
public class TreeNode : Tree {
  public Tree Left { get; set; }
  public Tree Right { get; set; }
}
public class TreeLeaf : Tree {
  public int Value { get; set; }
}
public abstract class TreeVisitor<T> {
 // ta metoda nie jest potrzebna ale ułatwia korzystanie z Visitora
  public T Visit( Tree tree ) {
    if (tree is TreeNode)
      return this.VisitNode( (TreeNode)tree );
    if (tree is TreeLeaf)
      return this.VisitLeaf( (TreeLeaf)tree );
    return default(T);
  }
  public virtual T VisitNode( TreeNode node ) {
  // tu wiedza o odwiedzaniu struktury
    if ( node != null ) {
      this.Visit( node.Left );
      this.Visit( node.Right );
    }
    return default(T);
  }
  public virtual T VisitLeaf( TreeLeaf leaf ) {
    return default(T);
  }
}

public class DepthTreeVisitor : TreeVisitor<int> {
  public override int VisitNode( TreeNode node ) {
    int l = 0, r = 0;
    if ( node != null ) {
      l = this.Visit( node.Left );
      r = this.Visit( node.Right );
    }
    return 1 + Math.Max( l, r );
  }
  public override int VisitLeaf( TreeLeaf leaf ) {
    return 1;
  }
}

public class MainClass {
  public static void Main() {
    Tree tree = new TreeNode {
      Left = new TreeNode {
        Left = new TreeLeaf { Value = 1 },
        Right = new TreeLeaf { Value = 2 }
      },
      Right = new TreeNode {
        Left = new TreeLeaf { Value = 3 },
        Right = new TreeNode {
          Left = new TreeLeaf { Value = 4 },
          Right = new TreeLeaf { Value = 5 }
        }
      }
    };
    TreeVisitor<int> visitor = new DepthTreeVisitor();
    int depth = visitor.Visit( tree );
    Console.WriteLine( depth );
  }
}
