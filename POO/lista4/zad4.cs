using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Linq;


public class TagBuilder
{
    public TagBuilder() { }

    public TagBuilder( StringBuilder Body )
    {
        this.body = Body;
    }
 
    public TagBuilder( string TagName, TagBuilder Parent )
    {
        this.tagName = TagName;
        this.parent = Parent;
    }
 
    private string        tagName;
    private bool          isIndented = false;
    private int           indentation = 0;
    private int           currIndentation = 0;
    private TagBuilder    parent;
    private StringBuilder body = new StringBuilder();
    private Dictionary<string, string> _attributes = new Dictionary<string, string>();
 
    public bool IsIndented
    {
        get { return isIndented; }
        set { isIndented = value; }
    }

    public int Indentation
    {
        get { return indentation; }
        set { indentation = value; }
    }
    public TagBuilder AddContent( string Content )
    {
        body.Append( Content );
        return this;
    }
 
    public TagBuilder AddContentFormat( string Format, params object[] args )
    {
        body.AppendFormat( Format, args );
        return this;
    }
 
    public TagBuilder StartTag( string TagName )
    {
        TagBuilder tag = new TagBuilder( TagName, this );
        tag.isIndented = isIndented;
        tag.indentation = indentation;
        tag.currIndentation = currIndentation + indentation;
        return tag;
    }
 
    public TagBuilder EndTag()
    {
        parent.AddContent( this.ToString() );
        return parent;
    }
 
    public TagBuilder AddAttribute( string Name, string Value )
    {
        _attributes.Add( Name, Value );
        return this;
    }
 
    public override string ToString()
    {
        StringBuilder tag = new StringBuilder();
 
        // preamble
        if ( !string.IsNullOrEmpty( this.tagName ) )
              if ( isIndented ) {
              for ( int i = 0; i < currIndentation - indentation; i++ )
              {
                  tag.Append( " " );
              }
            }
            // tag.AppendFormat( "{0}<{1}", indentation, tagName );
            tag.AppendFormat( "<{0}", tagName );
 
        if ( _attributes.Count > 0 )
        {
            tag.Append( " " );
            tag.Append( 
                string.Join( " ", 
                    _attributes
                        .Select( 
                            kvp => string.Format( "{0}=\"{1}\"", kvp.Key, kvp.Value ) )
                        .ToArray() ) );
        }
 
        // body/ending
        if ( body.Length > 0 )
        {
            string bodyString = body.ToString();
            if ( !string.IsNullOrEmpty( this.tagName) || this._attributes.Count > 0 )
                tag.Append( ">" );
                if ( isIndented && bodyString.Contains( "<" ) )
                    tag.Append( "\n" );

            tag.Append( bodyString );
            if ( !string.IsNullOrEmpty( this.tagName ) )
                tag.AppendFormat( "</{0}>", this.tagName );
                if ( isIndented )
                    tag.Append( "\n" );
        }
        else
            if ( !string.IsNullOrEmpty( this.tagName ) )
                tag.Append( "/>" );
 
        return tag.ToString();
    }
}

class Program
{
    static void Main(string[] args)
    {
        TestIndentedTagBuilding();
        TestNonIndentedTagBuilding();
    }

    public static void TestIndentedTagBuilding()
    {
        StringBuilder writer = new StringBuilder();
        TagBuilder tag = new TagBuilder(writer);
        tag.IsIndented = true;
        tag.Indentation = 4;
        tag.StartTag("parent")
            .AddAttribute("parentproperty1", "true")
            .AddAttribute("parentproperty2", "5")
            .StartTag("child1")
            .AddAttribute("childproperty1", "c")
            .AddContent("childbody")
            .EndTag()
            .StartTag("child2")
            .AddAttribute("childproperty2", "c")
            .AddContent("childbody")
            .EndTag()
            .EndTag()
            .StartTag("script")
            .AddContent("$.scriptbody();")
            .EndTag();

        string expectedOutput = "<parent parentproperty1=\"true\" parentproperty2=\"5\">\n" +
                                "    <child1 childproperty1=\"c\">childbody</child1>\n" +
                                "    <child2 childproperty2=\"c\">childbody</child2>\n" +
                                "</parent>\n" +
                                "<script>$.scriptbody();</script>\n";

        Console.WriteLine("TestIndentedTagBuilding:");
        Console.WriteLine("Expected Output:");
        Console.WriteLine(expectedOutput);
        Console.WriteLine("Actual Output:");
        Console.WriteLine(writer.ToString());
        Console.WriteLine("Test Result: " + (writer.ToString() == expectedOutput ? "Pass" : "Fail"));
        Console.WriteLine();
    }

    public static void TestNonIndentedTagBuilding()
    {
        StringBuilder writer = new StringBuilder();
        TagBuilder tag = new TagBuilder(writer);
        tag.IsIndented = false;
        tag.StartTag("parent")
            .AddAttribute("parentproperty1", "true")
            .AddAttribute("parentproperty2", "5")
            .StartTag("child1")
            .AddAttribute("childproperty1", "c")
            .AddContent("childbody")
            .EndTag()
            .StartTag("child2")
            .AddAttribute("childproperty2", "c")
            .AddContent("childbody")
            .EndTag()
            .EndTag()
            .StartTag("script")
            .AddContent("$.scriptbody();")
            .EndTag();

        string expectedOutput = "<parent parentproperty1=\"true\" parentproperty2=\"5\"><child1 childproperty1=\"c\">childbody</child1><child2 childproperty2=\"c\">childbody</child2></parent><script>$.scriptbody();</script>";

        Console.WriteLine("TestNonIndentedTagBuilding:");
        Console.WriteLine("Expected Output:");
        Console.WriteLine(expectedOutput);
        Console.WriteLine("Actual Output:");
        Console.WriteLine(writer.ToString());
        Console.WriteLine("Test Result: " + (writer.ToString() == expectedOutput ? "Pass" : "Fail"));
        Console.WriteLine();
    }

}
