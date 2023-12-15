/*
 * bip39_lib.c
 */

#include "bip39_lib.h"

const char bip39_words_a[136][10] = {
		"ABANDON", "ABILITY", "ABLE", "ABOUT", "ABOVE", "ABSENT", "ABSORB", "ABSTRACT", "ABSURD", "ABUSE", "ACCESS", "ACCIDENT", "ACCOUNT", "ACCUSE", "ACHIEVE", "ACID", "ACOUSTIC", "ACQUIRE", "ACROSS", "ACT",
		"ACTION", "ACTOR", "ACTRESS", "ACTUAL", "ADAPT", "ADD", "ADDICT", "ADDRESS", "ADJUST", "ADMIT", "ADULT", "ADVANCE", "ADVICE", "AEROBIC", "AFFAIR", "AFFORD", "AFRAID", "AGAIN", "AGE", "AGENT",
		"AGREE", "AHEAD", "AIM", "AIR", "AIRPORT", "AISLE", "ALARM", "ALBUM", "ALCOHOL", "ALERT", "ALIEN", "ALL", "ALLEY", "ALLOW", "ALMOST", "ALONE", "ALPHA", "ALREADY", "ALSO", "ALTER",
		"ALWAYS", "AMATEUR", "AMAZING", "AMONG", "AMOUNT", "AMUSED", "ANALYST", "ANCHOR", "ANCIENT", "ANGER", "ANGLE", "ANGRY", "ANIMAL", "ANKLE", "ANNOUNCE", "ANNUAL", "ANOTHER", "ANSWER", "ANTENNA", "ANTIQUE",
		"ANXIETY", "ANY", "APART", "APOLOGY", "APPEAR", "APPLE", "APPROVE", "APRIL", "ARCH", "ARCTIC", "AREA", "ARENA", "ARGUE", "ARM", "ARMED", "ARMOR", "ARMY", "AROUND", "ARRANGE", "ARREST",
		"ARRIVE", "ARROW", "ART", "ARTEFACT", "ARTIST", "ARTWORK", "ASK", "ASPECT", "ASSAULT", "ASSET", "ASSIST", "ASSUME", "ASTHMA", "ATHLETE", "ATOM", "ATTACK", "ATTEND", "ATTITUDE", "ATTRACT", "AUCTION",
		"AUDIT", "AUGUST", "AUNT", "AUTHOR", "AUTO", "AUTUMN", "AVERAGE", "AVOCADO", "AVOID", "AWAKE", "AWARE", "AWAY", "AWESOME", "AWFUL", "AWKWARD", "AXIS"
};

const char bip39_words_b[117][10] = {
		"BABY", "BACHELOR", "BACON", "BADGE", "BAG", "BALANCE", "BALCONY", "BALL", "BAMBOO", "BANANA", "BANNER", "BAR", "BARELY", "BARGAIN",
		"BARREL", "BASE", "BASIC", "BASKET", "BATTLE", "BEACH", "BEAN", "BEAUTY", "BECAUSE", "BECOME", "BEEF", "BEFORE", "BEGIN", "BEHAVE",
		"BEHIND", "BELIEVE", "BELOW", "BELT", "BENCH", "BENEFIT", "BEST", "BETRAY", "BETTER", "BETWEEN", "BEYOND", "BICYCLE", "BID", "BIKE",
		"BIND", "BIOLOGY", "BIRD", "BIRTH", "BITTER", "BLACK", "BLADE", "BLAME", "BLANKET", "BLAST", "BLEAK", "BLESS", "BLIND", "BLOOD",
		"BLOSSOM", "BLOUSE", "BLUE", "BLUR", "BLUSH", "BOARD", "BOAT", "BODY", "BOIL", "BOMB", "BONE", "BONUS", "BOOK", "BOOST", "BORDER", "BORING",
		"BORROW", "BOSS", "BOTTOM", "BOUNCE", "BOX", "BOY", "BRACKET", "BRAIN", "BRAND", "BRASS", "BRAVE", "BREAD", "BREEZE", "BRICK",
		"BRIDGE", "BRIEF", "BRIGHT", "BRING", "BRISK", "BROCCOLI", "BROKEN", "BRONZE", "BROOM", "BROTHER", "BROWN", "BRUSH", "BUBBLE", "BUDDY",
		"BUDGET", "BUFFALO", "BUILD", "BULB", "BULK", "BULLET", "BUNDLE", "BUNKER", "BURDEN", "BURGER", "BURST", "BUS", "BUSINESS", "BUSY", "BUTTER", "BUYER", "BUZZ"
};

const char bip39_words_c[186][10] = {
		"CABBAGE", "CABIN", "CABLE", "CACTUS", "CAGE", "CAKE", "CALL", "CALM", "CAMERA", "CAMP", "CAN", "CANAL", "CANCEL", "CANDY",
		"CANNON", "CANOE", "CANVAS", "CANYON", "CAPABLE", "CAPITAL", "CAPTAIN", "CAR", "CARBON", "CARD", "CARGO", "CARPET", "CARRY",
		"CART", "CASE", "CASH", "CASINO", "CASTLE", "CASUAL", "CAT", "CATALOG", "CATCH", "CATEGORY", "CATTLE", "CAUGHT", "CAUSE",
		"CAUTION", "CAVE", "CEILING", "CELERY", "CEMENT", "CENSUS", "CENTURY", "CEREAL", "CERTAIN", "CHAIR", "CHALK", "CHAMPION",
		"CHANGE", "CHAOS", "CHAPTER", "CHARGE", "CHASE", "CHAT", "CHEAP", "CHECK", "CHEESE", "CHEF", "CHERRY", "CHEST", "CHICKEN", "CHIEF",
		"CHILD", "CHIMNEY", "CHOICE", "CHOOSE", "CHRONIC", "CHUCKLE", "CHUNK", "CHURN", "CIGAR", "CINNAMON", "CIRCLE", "CITIZEN",
		"CITY", "CIVIL", "CLAIM", "CLAP", "CLARIFY", "CLAW", "CLAY", "CLEAN", "CLERK", "CLEVER", "CLICK", "CLIENT", "CLIFF", "CLIMB",
		"CLINIC", "CLIP", "CLOCK", "CLOG", "CLOSE", "CLOTH", "CLOUD", "CLOWN", "CLUB", "CLUMP", "CLUSTER", "CLUTCH", "COACH", "COAST",
		"COCONUT", "CODE", "COFFEE", "COIL", "COIN", "COLLECT", "COLOR", "COLUMN", "COMBINE", "COME", "COMFORT", "COMIC", "COMMON",
		"COMPANY", "CONCERT", "CONDUCT", "CONFIRM", "CONGRESS", "CONNECT", "CONSIDER", "CONTROL", "CONVINCE", "COOK", "COOL", "COPPER", "COPY",
		"CORAL", "CORE", "CORN", "CORRECT", "COST", "COTTON", "COUCH", "COUNTRY", "COUPLE", "COURSE", "COUSIN", "COVER", "COYOTE", "CRACK",
		"CRADLE", "CRAFT", "CRAM", "CRANE", "CRASH", "CRATER", "CRAWL", "CRAZY", "CREAM", "CREDIT", "CREEK", "CREW", "CRICKET", "CRIME",
		"CRISP", "CRITIC", "CROP", "CROSS", "CROUCH", "CROWD", "CRUCIAL", "CRUEL", "CRUISE", "CRUMBLE", "CRUNCH", "CRUSH", "CRY", "CRYSTAL",
		"CUBE", "CULTURE", "CUP", "CUPBOARD", "CURIOUS", "CURRENT", "CURTAIN", "CURVE", "CUSHION", "CUSTOM", "CUTE", "CYCLE"
};

const char bip39_words_d[112][10] = {
		"DAD", "DAMAGE", "DAMP", "DANCE", "DANGER", "DARING", "DASH", "DAUGHTER", "DAWN", "DAY", "DEAL", "DEBATE", "DEBRIS", "DECADE",
		"DECEMBER", "DECIDE", "DECLINE", "DECORATE", "DECREASE", "DEER", "DEFENSE", "DEFINE", "DEFY", "DEGREE", "DELAY", "DELIVER", "DEMAND",
		"DEMISE", "DENIAL", "DENTIST", "DENY", "DEPART", "DEPEND", "DEPOSIT", "DEPTH", "DEPUTY", "DERIVE", "DESCRIBE", "DESERT", "DESIGN", "DESK",
		"DESPAIR", "DESTROY", "DETAIL", "DETECT", "DEVELOP", "DEVICE", "DEVOTE", "DIAGRAM", "DIAL", "DIAMOND", "DIARY", "DICE", "DIESEL", "DIET",
		"DIFFER", "DIGITAL", "DIGNITY", "DILEMMA", "DINNER", "DINOSAUR", "DIRECT", "DIRT", "DISAGREE", "DISCOVER", "DISEASE", "DISH", "DISMISS",
		"DISORDER", "DISPLAY", "DISTANCE", "DIVERT", "DIVIDE", "DIVORCE", "DIZZY", "DOCTOR", "DOCUMENT", "DOG", "DOLL", "DOLPHIN", "DOMAIN",
		"DONATE", "DONKEY", "DONOR", "DOOR", "DOSE", "DOUBLE", "DOVE", "DRAFT", "DRAGON", "DRAMA", "DRASTIC", "DRAW", "DREAM", "DRESS", "DRIFT", "DRILL",
		"DRINK", "DRIP", "DRIVE", "DROP", "DRUM", "DRY", "DUCK", "DUMB", "DUNE", "DURING", "DUST", "DUTCH", "DUTY", "DWARF", "DYNAMIC"
};

const char bip39_words_e[100][10] = {
		"EAGER", "EAGLE", "EARLY", "EARN", "EARTH", "EASILY", "EAST", "EASY", "ECHO", "ECOLOGY", "ECONOMY", "EDGE", "EDIT", "EDUCATE",
		"EFFORT", "EGG", "EIGHT", "EITHER", "ELBOW", "ELDER", "ELECTRIC", "ELEGANT", "ELEMENT", "ELEPHANT", "ELEVATOR", "ELITE", "ELSE",
		"EMBARK", "EMBODY", "EMBRACE", "EMERGE", "EMOTION", "EMPLOY", "EMPOWER", "EMPTY", "ENABLE", "ENACT", "END", "ENDLESS", "ENDORSE",
		"ENEMY", "ENERGY", "ENFORCE", "ENGAGE", "ENGINE", "ENHANCE", "ENJOY", "ENLIST", "ENOUGH", "ENRICH", "ENROLL", "ENSURE", "ENTER", "ENTIRE",
		"ENTRY", "ENVELOPE", "EPISODE", "EQUAL", "EQUIP", "ERA", "ERASE", "ERODE", "EROSION", "ERROR", "ERUPT", "ESCAPE", "ESSAY", "ESSENCE",
		"ESTATE", "ETERNAL", "ETHICS", "EVIDENCE", "EVIL", "EVOKE", "EVOLVE", "EXACT", "EXAMPLE", "EXCESS", "EXCHANGE", "EXCITE", "EXCLUDE",
		"EXCUSE", "EXECUTE", "EXERCISE", "EXHAUST", "EXHIBIT", "EXILE", "EXIST", "EXIT", "EXOTIC", "EXPAND", "EXPECT", "EXPIRE", "EXPLAIN",
		"EXPOSE", "EXPRESS", "EXTEND", "EXTRA", "EYE", "EYEBROW"
};

const char bip39_words_f[106][10] = {
		"FABRIC", "FACE", "FACULTY", "FADE", "FAINT", "FAITH", "FALL", "FALSE", "FAME", "FAMILY", "FAMOUS", "FAN", "FANCY", "FANTASY",
		"FARM", "FASHION", "FAT", "FATAL", "FATHER", "FATIGUE", "FAULT", "FAVORITE", "FEATURE", "FEBRUARY", "FEDERAL", "FEE", "FEED",
		"FEEL", "FEMALE", "FENCE", "FESTIVAL", "FETCH", "FEVER", "FEW", "FIBER", "FICTION", "FIELD", "FIGURE", "FILE", "FILM", "FILTER",
		"FINAL", "FIND", "FINE", "FINGER", "FINISH", "FIRE", "FIRM", "FIRST", "FISCAL", "FISH", "FIT", "FITNESS", "FIX", "FLAG", "FLAME",
		"FLASH", "FLAT", "FLAVOR", "FLEE", "FLIGHT", "FLIP", "FLOAT", "FLOCK", "FLOOR", "FLOWER", "FLUID", "FLUSH", "FLY", "FOAM", "FOCUS",
		"FOG", "FOIL", "FOLD", "FOLLOW", "FOOD", "FOOT", "FORCE", "FOREST", "FORGET", "FORK", "FORTUNE", "FORUM", "FORWARD", "FOSSIL", "FOSTER",
		"FOUND", "FOX", "FRAGILE", "FRAME", "FREQUENT", "FRESH", "FRIEND", "FRINGE", "FROG", "FRONT", "FROST", "FROWN", "FROZEN", "FRUIT",
		"FUEL", "FUN", "FUNNY", "FURNACE", "FURY", "FUTURE"
};

const char bip39_words_g[76][10] = {
		"GADGET", "GAIN", "GALAXY", "GALLERY", "GAME", "GAP", "GARAGE", "GARBAGE", "GARDEN", "GARLIC", "GARMENT", "GAS", "GASP", "GATE", "GATHER", "GAUGE",
		"GAZE", "GENERAL", "GENIUS", "GENRE", "GENTLE", "GENUINE", "GESTURE", "GHOST", "GIANT", "GIFT", "GIGGLE", "GINGER", "GIRAFFE", "GIRL", "GIVE",
		"GLAD", "GLANCE", "GLARE", "GLASS", "GLIDE", "GLIMPSE", "GLOBE", "GLOOM", "GLORY", "GLOVE", "GLOW", "GLUE", "GOAT", "GODDESS", "GOLD", "GOOD",
		"GOOSE", "GORILLA", "GOSPEL", "GOSSIP", "GOVERN", "GOWN", "GRAB", "GRACE", "GRAIN", "GRANT", "GRAPE", "GRASS", "GRAVITY", "GREAT", "GREEN", "GRID",
		"GRIEF", "GRIT", "GROCERY", "GROUP", "GROW", "GRUNT", "GUARD", "GUESS", "GUIDE", "GUILT", "GUITAR", "GUN", "GYM"
};

const char bip39_words_h[64][10] = {
		"HABIT", "HAIR", "HALF", "HAMMER", "HAMSTER", "HAND", "HAPPY", "HARBOR", "HARD", "HARSH", "HARVEST", "HAT", "HAVE", "HAWK", "HAZARD", "HEAD",
		"HEALTH", "HEART", "HEAVY", "HEDGEHOG", "HEIGHT", "HELLO", "HELMET", "HELP", "HEN", "HERO", "HIDDEN", "HIGH", "HILL", "HINT", "HIP", "HIRE",
		"HISTORY", "HOBBY", "HOCKEY", "HOLD", "HOLE", "HOLIDAY", "HOLLOW", "HOME", "HONEY", "HOOD", "HOPE", "HORN", "HORROR", "HORSE", "HOSPITAL",
		"HOST", "HOTEL", "HOUR", "HOVER", "HUB", "HUGE", "HUMAN", "HUMBLE", "HUMOR", "HUNDRED", "HUNGRY", "HUNT", "HURDLE", "HURRY", "HURT", "HUSBAND", "HYBRID"
};

const char bip39_words_i[55][10] = {
		"ICE", "ICON", "IDEA", "IDENTIFY", "IDLE", "IGNORE", "ILL", "ILLEGAL", "ILLNESS", "IMAGE", "IMITATE", "IMMENSE", "IMMUNE", "IMPACT", "IMPOSE",
		"IMPROVE", "IMPULSE", "INCH", "INCLUDE", "INCOME", "INCREASE", "INDEX", "INDICATE", "INDOOR", "INDUSTRY", "INFANT", "INFLICT", "INFORM", "INHALE",
		"INHERIT", "INITIAL", "INJECT", "INJURY", "INMATE", "INNER", "INNOCENT", "INPUT", "INQUIRY", "INSANE", "INSECT", "INSIDE", "INSPIRE", "INSTALL",
		"INTACT", "INTEREST", "INTO", "INVEST", "INVITE", "INVOLVE", "IRON", "ISLAND", "ISOLATE", "ISSUE", "ITEM", "IVORY"
};

const char bip39_words_j[20][10] = {
		"JACKET", "JAGUAR", "JAR", "JAZZ", "JEALOUS", "JEANS", "JELLY", "JEWEL", "JOB", "JOIN", "JOKE", "JOURNEY", "JOY", "JUDGE", "JUICE", "JUMP", "JUNGLE", "JUNIOR", "JUNK", "JUST"
};

const char bip39_words_k[20][10] = {
		"KANGAROO", "KEEN", "KEEP", "KETCHUP", "KEY", "KICK", "KID", "KIDNEY", "KIND", "KINGDOM", "KISS", "KIT", "KITCHEN", "KITE", "KITTEN", "KIWI", "KNEE", "KNIFE", "KNOCK", "KNOW"
};

const char bip39_words_l[76][10] = {
		"LAB", "LABEL", "LABOR", "LADDER", "LADY", "LAKE", "LAMP", "LANGUAGE", "LAPTOP", "LARGE", "LATER", "LATIN", "LAUGH", "LAUNDRY", "LAVA", "LAW",
		"LAWN", "LAWSUIT", "LAYER", "LAZY", "LEADER", "LEAF", "LEARN", "LEAVE", "LECTURE", "LEFT", "LEG", "LEGAL", "LEGEND", "LEISURE", "LEMON", "LEND",
		"LENGTH", "LENS", "LEOPARD", "LESSON", "LETTER", "LEVEL", "LIAR", "LIBERTY", "LIBRARY", "LICENSE", "LIFE", "LIFT", "LIGHT", "LIKE", "LIMB",
		"LIMIT", "LINK", "LION", "LIQUID", "LIST", "LITTLE", "LIVE", "LIZARD", "LOAD", "LOAN", "LOBSTER", "LOCAL", "LOCK", "LOGIC", "LONELY", "LONG",
		"LOOP", "LOTTERY", "LOUD", "LOUNGE", "LOVE", "LOYAL", "LUCKY", "LUGGAGE", "LUMBER", "LUNAR", "LUNCH", "LUXURY", "LYRICS"
};

const char bip39_words_m[105][10] = {
		"MACHINE", "MAD", "MAGIC", "MAGNET", "MAID", "MAIL", "MAIN", "MAJOR", "MAKE", "MAMMAL", "MAN", "MANAGE", "MANDATE", "MANGO", "MANSION", "MANUAL",
		"MAPLE", "MARBLE", "MARCH", "MARGIN", "MARINE", "MARKET", "MARRIAGE", "MASK", "MASS", "MASTER", "MATCH", "MATERIAL", "MATH", "MATRIX", "MATTER", "MAXIMUM",
		"MAZE", "MEADOW", "MEAN", "MEASURE", "MEAT", "MECHANIC", "MEDAL", "MEDIA", "MELODY", "MELT", "MEMBER", "MEMORY", "MENTION", "MENU", "MERCY", "MERGE",
		"MERIT", "MERRY", "MESH", "MESSAGE", "METAL", "METHOD", "MIDDLE", "MIDNIGHT", "MILK", "MILLION", "MIMIC", "MIND", "MINIMUM", "MINOR", "MINUTE", "MIRACLE",
		"MIRROR", "MISERY", "MISS", "MISTAKE", "MIX", "MIXED", "MIXTURE", "MOBILE", "MODEL", "MODIFY", "MOM", "MOMENT", "MONITOR", "MONKEY", "MONSTER", "MONTH",
		"MOON", "MORAL", "MORE", "MORNING", "MOSQUITO", "MOTHER", "MOTION", "MOTOR", "MOUNTAIN", "MOUSE", "MOVE", "MOVIE", "MUCH", "MUFFIN", "MULE", "MULTIPLY",
		"MUSCLE", "MUSEUM", "MUSHROOM", "MUSIC", "MUST", "MUTUAL", "MYSELF", "MYSTERY", "MYTH"
};

const char bip39_words_n[41][10] = {
		"NAIVE", "NAME", "NAPKIN", "NARROW", "NASTY", "NATION", "NATURE", "NEAR", "NECK", "NEED", "NEGATIVE", "NEGLECT", "NEITHER", "NEPHEW", "NERVE", "NEST",
		"NET", "NETWORK", "NEUTRAL", "NEVER", "NEWS", "NEXT", "NICE", "NIGHT", "NOBLE", "NOISE", "NOMINEE", "NOODLE", "NORMAL", "NORTH", "NOSE", "NOTABLE", "NOTE",
		"NOTHING", "NOTICE", "NOVEL", "NOW", "NUCLEAR", "NUMBER", "NURSE", "NUT"
};

const char bip39_words_o[55][10] = {
		"OAK", "OBEY", "OBJECT", "OBLIGE", "OBSCURE", "OBSERVE", "OBTAIN", "OBVIOUS", "OCCUR", "OCEAN", "OCTOBER", "ODOR", "OFF", "OFFER", "OFFICE", "OFTEN", "OIL",
		"OKAY", "OLD", "OLIVE", "OLYMPIC", "OMIT", "ONCE", "ONE", "ONION", "ONLINE", "ONLY", "OPEN", "OPERA", "OPINION", "OPPOSE", "OPTION", "ORANGE", "ORBIT",
		"ORCHARD", "ORDER", "ORDINARY", "ORGAN", "ORIENT", "ORIGINAL", "ORPHAN", "OSTRICH", "OTHER", "OUTDOOR", "OUTER", "OUTPUT", "OUTSIDE", "OVAL", "OVEN",
		"OVER", "OWN", "OWNER", "OXYGEN", "OYSTER", "OZONE"
};

const char bip39_words_p[132][10] = {
		"PACT", "PADDLE", "PAGE", "PAIR", "PALACE", "PALM", "PANDA", "PANEL", "PANIC", "PANTHER", "PAPER", "PARADE", "PARENT", "PARK", "PARROT", "PARTY", "PASS", "PATCH", "PATH", "PATIENT",
		"PATROL", "PATTERN", "PAUSE", "PAVE", "PAYMENT", "PEACE", "PEANUT", "PEAR", "PEASANT", "PELICAN", "PEN", "PENALTY", "PENCIL", "PEOPLE", "PEPPER", "PERFECT", "PERMIT", "PERSON", "PET", "PHONE",
		"PHOTO", "PHRASE", "PHYSICAL", "PIANO", "PICNIC", "PICTURE", "PIECE", "PIG", "PIGEON", "PILL", "PILOT", "PINK", "PIONEER", "PIPE", "PISTOL", "PITCH", "PIZZA", "PLACE", "PLANET", "PLASTIC",
		"PLATE", "PLAY", "PLEASE", "PLEDGE", "PLUCK", "PLUG", "PLUNGE", "POEM", "POET", "POINT", "POLAR", "POLE", "POLICE", "POND", "PONY", "POOL", "POPULAR", "PORTION", "POSITION", "POSSIBLE",
		"POST", "POTATO", "POTTERY", "POVERTY", "POWDER", "POWER", "PRACTICE", "PRAISE", "PREDICT", "PREFER", "PREPARE", "PRESENT", "PRETTY", "PREVENT", "PRICE", "PRIDE", "PRIMARY", "PRINT", "PRIORITY", "PRISON",
		"PRIVATE", "PRIZE", "PROBLEM", "PROCESS", "PRODUCE", "PROFIT", "PROGRAM", "PROJECT", "PROMOTE", "PROOF", "PROPERTY", "PROSPER", "PROTECT", "PROUD", "PROVIDE", "PUBLIC", "PUDDING", "PULL", "PULP", "PULSE",
		"PUMPKIN", "PUNCH", "PUPIL", "PUPPY", "PURCHASE", "PURITY", "PURPOSE", "PURSE", "PUSH", "PUT", "PUZZLE", "PYRAMID"
};

const char bip39_words_q[8][10] = {
		"QUALITY", "QUANTUM", "QUARTER", "QUESTION", "QUICK", "QUIT", "QUIZ", "QUOTE"
};

const char bip39_words_r[108][10] = {
		"RABBIT", "RACCOON", "RACE", "RACK", "RADAR", "RADIO", "RAIL", "RAIN", "RAISE", "RALLY", "RAMP", "RANCH", "RANDOM", "RANGE", "RAPID", "RARE", "RATE", "RATHER", "RAVEN", "RAW",
		"RAZOR", "READY", "REAL", "REASON", "REBEL", "REBUILD", "RECALL", "RECEIVE", "RECIPE", "RECORD", "RECYCLE", "REDUCE", "REFLECT", "REFORM", "REFUSE", "REGION", "REGRET", "REGULAR",
		"REJECT", "RELAX", "RELEASE", "RELIEF", "RELY", "REMAIN", "REMEMBER", "REMIND", "REMOVE", "RENDER", "RENEW", "RENT", "REOPEN", "REPAIR", "REPEAT", "REPLACE", "REPORT", "REQUIRE",
		"RESCUE", "RESEMBLE", "RESIST", "RESOURCE", "RESPONSE", "RESULT", "RETIRE", "RETREAT", "RETURN", "REUNION", "REVEAL", "REVIEW", "REWARD", "RHYTHM", "RIB", "RIBBON", "RICE",
		"RICH", "RIDE", "RIDGE", "RIFLE", "RIGHT", "RIGID", "RING", "RIOT", "RIPPLE", "RISK", "RITUAL", "RIVAL", "RIVER", "ROAD", "ROAST", "ROBOT", "ROBUST", "ROCKET", "ROMANCE",
		"ROOF", "ROOKIE", "ROOM", "ROSE", "ROTATE", "ROUGH", "ROUND", "ROUTE", "ROYAL", "RUBBER", "RUDE", "RUG", "RULE", "RUN", "RUNWAY", "RURAL"
};

const char bip39_words_s[250][10] = {
		"SAD", "SADDLE", "SADNESS", "SAFE", "SAIL", "SALAD", "SALMON", "SALON", "SALT", "SALUTE", "SAME", "SAMPLE", "SAND", "SATISFY", "SATOSHI", "SAUCE", "SAUSAGE", "SAVE", "SAY", "SCALE",
		"SCAN", "SCARE", "SCATTER", "SCENE", "SCHEME", "SCHOOL", "SCIENCE", "SCISSORS", "SCORPION", "SCOUT", "SCRAP", "SCREEN", "SCRIPT", "SCRUB", "SEA", "SEARCH", "SEASON", "SEAT", "SECOND", "SECRET",
		"SECTION", "SECURITY", "SEED", "SEEK", "SEGMENT", "SELECT", "SELL", "SEMINAR", "SENIOR", "SENSE", "SENTENCE", "SERIES", "SERVICE", "SESSION", "SETTLE", "SETUP", "SEVEN", "SHADOW", "SHAFT", "SHALLOW",
		"SHARE", "SHED", "SHELL", "SHERIFF", "SHIELD", "SHIFT", "SHINE", "SHIP", "SHIVER", "SHOCK", "SHOE", "SHOOT", "SHOP", "SHORT", "SHOULDER", "SHOVE", "SHRIMP", "SHRUG", "SHUFFLE", "SHY",
		"SIBLING", "SICK", "SIDE", "SIEGE", "SIGHT", "SIGN", "SILENT", "SILK", "SILLY", "SILVER", "SIMILAR", "SIMPLE", "SINCE", "SING", "SIREN", "SISTER", "SITUATE", "SIX", "SIZE", "SKATE",
		"SKETCH", "SKI", "SKILL", "SKIN", "SKIRT", "SKULL", "SLAB", "SLAM", "SLEEP", "SLLENDER", "SLICE", "SLIDE", "SLIGHT", "SLIM", "SLOGAN", "SLOT", "SLOW", "SLUSH", "SMALL", "SMART",
		"SMILE", "SMOKE", "SMOOTH", "SNACK", "SNAKE", "SNAP", "SNIFF", "SNOW", "SOAP", "SOCCER", "SOCIAL", "SOCK", "SODA", "SOFT", "SOLAR", "SOLDIER", "SOLID", "SOLUTION", "SOLVE", "SOMEONE",
		"SONG", "SOON", "SORRY", "SORT", "SOUL", "SOUND", "SOUP", "SOURCE", "SOUTH", "SPACE", "SPARE", "SPATIAL", "SPAWN", "SPEAK", "SPECIAL", "SPEED", "SPELL", "SPEND", "SPHERE", "SPICE",
		"SPIDER", "SPIKE", "SPIN", "SPIRIT", "SPLIT", "SPOIL", "SPONSOR", "SPOON", "SPORT", "SPOT", "SPRAY", "SPREAD", "SPRING", "SPY", "SQUARE", "SQUEEZE", "SQUIRREL", "STABLE", "STADIUM", "STAFF",
		"STAGE", "STAIRS", "STAMP", "STAND", "START", "STATE", "STAY", "STEAK", "STEEL", "STEM", "STEP", "STEREO", "STICK", "STILL", "STING", "STOCK", "STOMACH", "STONE", "STOOL", "STORY",
		"STOVE", "STRATEGY", "STREET", "STRIKE", "STRONG", "STRUGGLE", "STUDENT", "STUFF", "STUMBLE", "STYLE", "SUBJECT", "SUBMIT", "SUBWAY", "SUCCESS", "SUCH", "SUDDEN", "SUFFER", "SUGAR", "SUGGEST", "SUIT",
		"SUMMER", "SUN", "SUNNY", "SUNSET", "SUPER", "SUPPLY", "SUPREME", "SURE", "SURFACE", "SURGE", "SURPRISE", "SURROUND", "SURVEY", "SUSPECT", "SUSTAIN", "SWALLOW", "SWAMP", "SWAP", "SWARM", "SWEAR",
		"SWEET", "SWIFT", "SWIM", "SWING", "SWITCH", "SWORD", "SYMBOL", "SYMPTOM", "SYRUP", "SYSTEM"
};

const char bip39_words_t[121][10] = {
		"TABLE", "TACKLE", "TAG", "TAIL", "TALENT", "TALK", "TANK", "TAPE", "TARGET", "TASK", "TASTE", "TATTOO", "TAXI", "TEACH", "TEAM", "TELL", "TEN", "TENANT", "TENNIS", "TENT",
		"TERM", "TEST", "TEXT", "THANK", "THAT", "THEME", "THEN", "THEORY", "THERE", "THEY", "THING", "THIS", "THOUGHT", "THREE", "THRIVE", "THROW", "THUMB", "THUNDER", "TICKET",
		"TIDE", "TIGER", "TILT", "TIMBER", "TIME", "TINY", "TIP", "TIRED", "TISSUE", "TITLE", "TOAST", "TOBACCO", "TODAY", "TODDLER", "TOE", "TOGETHER", "TOILET", "TOKEN", "TOMATO",
		"TOMORROW", "TONE", "TONGUE", "TONIGHT", "TOOL", "TOOTH", "TOP", "TOPIC", "TOPPLE", "TORCH", "TORNADO", "TORTOISE", "TOSS", "TOTAL", "TOURIST", "TOWARD", "TOWER", "TOWN",
		"TOY", "TRACK", "TRADE", "TRAFFIC", "TRAGIC", "TRAIN", "TRANSFER", "TRAP", "TRASH", "TRAVEL", "TRAY", "TREAT", "TREE", "TREND", "TRIAL", "TRIBE", "TRICK", "TRIGGER",
		"TRIM", "TRIP", "TROPHY", "TROUBLE", "TRUCK", "TRUE", "TRULY", "TRUMPET", "TRUST", "TRUTH", "TRY", "TUBE", "TUITION", "TUMBLE", "TUNA", "TUNNEL", "TURKEY", "TURN",
		"TURTLE", "TWELVE", "TWENTY", "TWICE", "TWIN", "TWIST", "TWO", "TYPE", "TYPICAL"
};

const char bip39_words_u[35][10] = {
		"UGLY", "UMBRELLA", "UNABLE", "UNAWARE", "UNCLE", "UNCOVER", "UNDER", "UNDO", "UNFAIR", "UNFOLD", "UNHAPPY", "UNIFORM", "UNIQUE", "UNIT", "UNIVERSE", "UNKNOWN", "UNLOCK", "UNTIL",
		"UNUSUAL", "UNVEIL", "UPDATE", "UPGRADE", "UPHOLD", "UPON", "UPPER", "UPSET", "URBAN", "URGE", "USAGE", "USE", "USED", "USEFUL", "USELESS", "USUAL", "UTILITY"
};

const char bip39_words_v[46][10] = {
		"VACANT", "VACUUM", "VAGUE", "VALID", "VALLEY", "VALVE", "VAN", "VANISH", "VAPOR", "VARIOUS", "VAST", "VAULT", "VEHICLE", "VELVET", "VENDOR", "VENTURE", "VENUE", "VERB", "VERIFY", "VERSION",
		"VERY", "VESSEL", "VETERAN", "VIABLE", "VIBRANT", "VICIOUS", "VICTORY", "VIDEO", "VIEW", "VILLAGE", "VINTAGE", "VIOLIN", "VIRTUAL", "VIRUS", "VISA", "VISIT", "VISUAL", "VITAL", "VIVID", "VOCAL",
		"VOICE", "VOID", "VOLCANO", "VOLUME", "VOTE", "VOYAGE"
};

const char bip39_words_w[69][10] = {
		"WAGE", "WAGON", "WAIT", "WALK", "WALL", "WALNUT", "WANT", "WARFARE", "WARM", "WARRIOR", "WASH", "WASP", "WASTE", "WATER", "WAVE", "WAY", "WEALTH", "WEAPON", "WEAR", "WEASEL",
		"WEATHER", "WEB", "WEDDING", "WEEKEND", "WEIRD", "WELCOME", "WEST", "WET", "WHALE", "WHAT", "WHEAT", "WHEEL", "WHEN", "WHERE", "WHIP", "WHISPER", "WIDE", "WIDTH", "WIFE",
		"WILD", "WILL", "WIN", "WINDOW", "WINE", "WING", "WINK", "WINNER", "WINTER", "WIRE", "WISDOM", "WISE", "WISH", "WITNESS", "WOLF", "WOMAN", "WONDER", "WOOD", "WOOL", "WORD",
		"WORK", "WORLD", "WORRY", "WORTH", "WRAP", "WRECK", "WRESTLE", "WRIST", "WRITE", "WRONG"
};

const char bip39_words_y[6][10] = {
		"YARD", "YEAR", "YELLOW", "YOU", "YOUNG", "YOUTH"
};

const char bip39_words_z[4][10] = {
		"ZEBRA", "ZERO", "ZONE", "ZOO"
};

/******************************************************************************************************************************************************************************
 ***** Función 		: bool getBip39Word(char *word_to_predict)
 ***** Descripción 	: Predictibilidad de palabra de diccionario bip39
 ***** Parámetros 	:	- word_to_predict --> Puntero a array
 ***** Respuesta 	:	- true 	--> OK
 ***** 					- false	--> ERROR
 ******************************************************************************************************************************************************************************/
bool getBip39Word(char *word_to_predict)
{
	switch(word_to_predict[0])
	{
	case 'A':
		for(int i=0; i<sizeof(bip39_words_a)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_a[i][0]) && (word_to_predict[1] == bip39_words_a[i][1]) && (word_to_predict[2] == bip39_words_a[i][2]) && (word_to_predict[3] == bip39_words_a[i][3])){
				memcpy(word_to_predict, bip39_words_a[i], 10);
				return true;
			}
		}
		break;

	case 'B':
		for(int i=0; i<sizeof(bip39_words_b)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_b[i][0]) && (word_to_predict[1] == bip39_words_b[i][1]) && (word_to_predict[2] == bip39_words_b[i][2]) && (word_to_predict[3] == bip39_words_b[i][3])){
				memcpy(word_to_predict, bip39_words_b[i], 10);
				return true;
			}
		}
		break;

	case 'C':
		for(int i=0; i<sizeof(bip39_words_c)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_c[i][0]) && (word_to_predict[1] == bip39_words_c[i][1]) && (word_to_predict[2] == bip39_words_c[i][2]) && (word_to_predict[3] == bip39_words_c[i][3])){
				memcpy(word_to_predict, bip39_words_c[i], 10);
				return true;
			}
		}
		break;

	case 'D':
		for(int i=0; i<sizeof(bip39_words_d)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_d[i][0]) && (word_to_predict[1] == bip39_words_d[i][1]) && (word_to_predict[2] == bip39_words_d[i][2]) && (word_to_predict[3] == bip39_words_d[i][3])){
				memcpy(word_to_predict, bip39_words_d[i], 10);
				return true;
			}
		}
		break;

	case 'E':
		for(int i=0; i<sizeof(bip39_words_e)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_e[i][0]) && (word_to_predict[1] == bip39_words_e[i][1]) && (word_to_predict[2] == bip39_words_e[i][2]) && (word_to_predict[3] == bip39_words_e[i][3])){
				memcpy(word_to_predict, bip39_words_e[i], 10);
				return true;
			}
		}
		break;

	case 'F':
		for(int i=0; i<sizeof(bip39_words_f)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_f[i][0]) && (word_to_predict[1] == bip39_words_f[i][1]) && (word_to_predict[2] == bip39_words_f[i][2]) && (word_to_predict[3] == bip39_words_f[i][3])){
				memcpy(word_to_predict, bip39_words_f[i], 10);
				return true;
			}
		}
		break;

	case 'G':
		for(int i=0; i<sizeof(bip39_words_g)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_g[i][0]) && (word_to_predict[1] == bip39_words_g[i][1]) && (word_to_predict[2] == bip39_words_g[i][2]) && (word_to_predict[3] == bip39_words_g[i][3])){
				memcpy(word_to_predict, bip39_words_g[i], 10);
				return true;
			}
		}
		break;

	case 'H':
		for(int i=0; i<sizeof(bip39_words_h)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_h[i][0]) && (word_to_predict[1] == bip39_words_h[i][1]) && (word_to_predict[2] == bip39_words_h[i][2]) && (word_to_predict[3] == bip39_words_h[i][3])){
				memcpy(word_to_predict, bip39_words_h[i], 10);
				return true;
			}
		}
		break;

	case 'I':
		for(int i=0; i<sizeof(bip39_words_i)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_i[i][0]) && (word_to_predict[1] == bip39_words_i[i][1]) && (word_to_predict[2] == bip39_words_i[i][2]) && (word_to_predict[3] == bip39_words_i[i][3])){
				memcpy(word_to_predict, bip39_words_i[i], 10);
				return true;
			}
		}
		break;

	case 'J':
		for(int i=0; i<sizeof(bip39_words_j)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_j[i][0]) && (word_to_predict[1] == bip39_words_j[i][1]) && (word_to_predict[2] == bip39_words_j[i][2]) && (word_to_predict[3] == bip39_words_j[i][3])){
				memcpy(word_to_predict, bip39_words_j[i], 10);
				return true;
			}
		}
		break;

	case 'K':
		for(int i=0; i<sizeof(bip39_words_k)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_k[i][0]) && (word_to_predict[1] == bip39_words_k[i][1]) && (word_to_predict[2] == bip39_words_k[i][2]) && (word_to_predict[3] == bip39_words_k[i][3])){
				memcpy(word_to_predict, bip39_words_k[i], 10);
				return true;
			}
		}
		break;

	case 'L':
		for(int i=0; i<sizeof(bip39_words_l)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_l[i][0]) && (word_to_predict[1] == bip39_words_l[i][1]) && (word_to_predict[2] == bip39_words_l[i][2]) && (word_to_predict[3] == bip39_words_l[i][3])){
				memcpy(word_to_predict, bip39_words_l[i], 10);
				return true;
			}
		}
		break;

	case 'M':
		for(int i=0; i<sizeof(bip39_words_m)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_m[i][0]) && (word_to_predict[1] == bip39_words_m[i][1]) && (word_to_predict[2] == bip39_words_m[i][2]) && (word_to_predict[3] == bip39_words_m[i][3])){
				memcpy(word_to_predict, bip39_words_m[i], 10);
				return true;
			}
		}
		break;

	case 'N':
		for(int i=0; i<sizeof(bip39_words_n)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_n[i][0]) && (word_to_predict[1] == bip39_words_n[i][1]) && (word_to_predict[2] == bip39_words_n[i][2]) && (word_to_predict[3] == bip39_words_n[i][3])){
				memcpy(word_to_predict, bip39_words_n[i], 10);
				return true;
			}
		}
		break;

	case 'O':
		for(int i=0; i<sizeof(bip39_words_o)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_o[i][0]) && (word_to_predict[1] == bip39_words_o[i][1]) && (word_to_predict[2] == bip39_words_o[i][2]) && (word_to_predict[3] == bip39_words_o[i][3])){
				memcpy(word_to_predict, bip39_words_o[i], 10);
				return true;
			}
		}
		break;

	case 'P':
		for(int i=0; i<sizeof(bip39_words_p)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_p[i][0]) && (word_to_predict[1] == bip39_words_p[i][1]) && (word_to_predict[2] == bip39_words_p[i][2]) && (word_to_predict[3] == bip39_words_p[i][3])){
				memcpy(word_to_predict, bip39_words_p[i], 10);
				return true;
			}
		}
		break;

	case 'Q':
		for(int i=0; i<sizeof(bip39_words_q)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_q[i][0]) && (word_to_predict[1] == bip39_words_q[i][1]) && (word_to_predict[2] == bip39_words_q[i][2]) && (word_to_predict[3] == bip39_words_q[i][3])){
				memcpy(word_to_predict, bip39_words_q[i], 10);
				return true;
			}
		}
		break;

	case 'R':
		for(int i=0; i<sizeof(bip39_words_r)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_r[i][0]) && (word_to_predict[1] == bip39_words_r[i][1]) && (word_to_predict[2] == bip39_words_r[i][2]) && (word_to_predict[3] == bip39_words_r[i][3])){
				memcpy(word_to_predict, bip39_words_r[i], 10);
				return true;
			}
		}
		break;

	case 'S':
		for(int i=0; i<sizeof(bip39_words_s)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_s[i][0]) && (word_to_predict[1] == bip39_words_s[i][1]) && (word_to_predict[2] == bip39_words_s[i][2]) && (word_to_predict[3] == bip39_words_s[i][3])){
				memcpy(word_to_predict, bip39_words_s[i], 10);
				return true;
			}
		}
		break;

	case 'T':
		for(int i=0; i<sizeof(bip39_words_t)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_t[i][0]) && (word_to_predict[1] == bip39_words_t[i][1]) && (word_to_predict[2] == bip39_words_t[i][2]) && (word_to_predict[3] == bip39_words_t[i][3])){
				memcpy(word_to_predict, bip39_words_t[i], 10);
				return true;
			}
		}
		break;

	case 'U':
		for(int i=0; i<sizeof(bip39_words_u)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_u[i][0]) && (word_to_predict[1] == bip39_words_u[i][1]) && (word_to_predict[2] == bip39_words_u[i][2]) && (word_to_predict[3] == bip39_words_u[i][3])){
				memcpy(word_to_predict, bip39_words_u[i], 10);
				return true;
			}
		}
		break;

	case 'V':
		for(int i=0; i<sizeof(bip39_words_v)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_v[i][0]) && (word_to_predict[1] == bip39_words_v[i][1]) && (word_to_predict[2] == bip39_words_v[i][2]) && (word_to_predict[3] == bip39_words_v[i][3])){
				memcpy(word_to_predict, bip39_words_v[i], 10);
				return true;
			}
		}
		break;

	case 'W':
		for(int i=0; i<sizeof(bip39_words_w)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_w[i][0]) && (word_to_predict[1] == bip39_words_w[i][1]) && (word_to_predict[2] == bip39_words_w[i][2]) && (word_to_predict[3] == bip39_words_w[i][3])){
				memcpy(word_to_predict, bip39_words_w[i], 10);
				return true;
			}
		}
		break;

	case 'Y':
		for(int i=0; i<sizeof(bip39_words_y)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_y[i][0]) && (word_to_predict[1] == bip39_words_y[i][1]) && (word_to_predict[2] == bip39_words_y[i][2]) && (word_to_predict[3] == bip39_words_y[i][3])){
				memcpy(word_to_predict, bip39_words_y[i], 10);
				return true;
			}
		}
		break;

	case 'Z':
		for(int i=0; i<sizeof(bip39_words_z)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_z[i][0]) && (word_to_predict[1] == bip39_words_z[i][1]) && (word_to_predict[2] == bip39_words_z[i][2]) && (word_to_predict[3] == bip39_words_z[i][3])){
				memcpy(word_to_predict, bip39_words_z[i], 10);
				return true;
			}
		}
		break;

	default:
	case 'X':
		break;

	}

	return false;
}




