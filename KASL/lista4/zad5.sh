cflag=
colorflag=
colorval=
gflag=
gval=
name=

VARS=`getopt -o cg::hvw --long capitalize,color::,greeting::,help,version,world -n 'zad5.sh' -- "$@"`

if [ $? != 0 ] ; then echo "Terminating..." >&2 ; exit 1 ; fi

echo $VARS

eval set -- "$VARS"

while true; do
    echo "var: $1"
    case $1 in
        -c|--capitalize)
            cflag=1
            shift
            ;;
        --color)
            colorflag=1
            colorval=$2
            shift 2
            ;;
        -g|--greeting)
            gflag=1
            gval=$2
            echo $gval
            shift
            shift
            ;;
        -h|--help)
            echo "Usage: zad5.sh [OPTIONS] NAME"
            echo "Options:"
            echo "  -c, --capitalize"
            echo "  --color=[never|auto|always]"
            echo "  -g text, --greeting=text"
            echo "  -h, --help"
            echo "  -v, --version"
            echo "  -w, --world"
            exit 0
            ;;
        -v|--version)
            echo "zad5.sh version 0.1"
            exit 0
            ;;
        -w|--world)
            echo "Hello, world!"
            shift
            ;;
        --)
            shift
            name=$2
            break
            ;;
        *)
            echo "Internal error!"
            exit 1
            ;;
    esac
done

echo "cflag: $cflag"
echo "colorflag: $colorflag"
echo "colorval: $colorval"
echo "gflag: $gflag"
echo "gval: $gval"
echo "name: $name"