cflag=
colorflag=
colorval="auto"
wflag=
gflag=
name=
greeting="Hello"
wrld="world"
clrb=""
clre=""

VARS=`getopt -o cg::hvw --long capitalize,color::,greeting::,help,version,world -n 'zad5.sh' -- "$@"`

if [ $? != 0 ] ; then echo "Terminating..." >&2 ; exit 1 ; fi

# echo $VARS

eval set -- "$VARS"

while true; do
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
            greeting=$2
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
            wflag=1
            shift
            ;;
        --)
            name=$2
            break
            ;;
        *)
            echo "Internal error!"
            exit 1
            ;;
    esac
done

# echo "cflag: $cflag"
# echo "colorflag: $colorflag"
# echo "colorval: $colorval"
# echo "gflag: $gflag"
# echo "name: $name"

if [ -z $name ] && [ -z $wflag ]; then
    echo "No name provided!"
    exit 1
fi

case $colorval in
    never)
        ;;
    auto)
        if [ -t 1 ]; then
            clrb="\033[31m"
            clre="\033[0m"
        else
            clrb=""
            clre=""
        fi
        ;;
    always)
        clrb="\033[31m"
        clre="\033[0m"
        ;;
    *)
        echo "Invalid color value!"
        echo "Valid values: never, auto, always"
        exit 1
        ;;
esac

if [ $cflag ]; then
    wrld=`echo $wrld | tr '[:lower:]' '[:upper:]'`
    name=`echo $name | tr '[:lower:]' '[:upper:]'`
fi

if [ $wflag ]; then
    echo -e "$greeting, $clrb$wrld$clre!"
fi

if [ $name ]; then
    echo -e "$greeting, $clrb$name$clre!"
fi