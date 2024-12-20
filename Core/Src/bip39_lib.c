/**
 ******************************************************************************
 * @file           : bip39_lib.c
 * @brief          : Seed bip39 library
 ******************************************************************************
 * @attention
 *
 * Portion Copyright (C) 2024 Semilla3 OÜ.  All Rights Reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "bip39_lib.h"

const char bip39_words_a[136][10] = {
		"abandon", "ability", "able", "about", "above", "absent", "absorb", "abstract", "absurd", "abuse", "access", "accident", "account", "accuse", "achieve", "acid", "acoustic", "acquire", "across", "act",
		"action", "actor", "actress", "actual", "adapt", "add", "addict", "address", "adjust", "admit", "adult", "advance", "advice", "aerobic", "affair", "afford", "afraid", "again", "age", "agent",
		"agree", "ahead", "aim", "air", "airport", "aisle", "alarm", "album", "alcohol", "alert", "alien", "all", "alley", "allow", "almost", "alone", "alpha", "already", "also", "alter",
		"always", "amateur", "amazing", "among", "amount", "amused", "analyst", "anchor", "ancient", "anger", "angle", "angry", "animal", "ankle", "announce", "annual", "another", "answer", "antenna", "antique",
		"anxiety", "any", "apart", "apology", "appear", "apple", "approve", "april", "arch", "arctic", "area", "arena", "argue", "arm", "armed", "armor", "army", "around", "arrange", "arrest",
		"arrive", "arrow", "art", "artefact", "artist", "artwork", "ask", "aspect", "assault", "asset", "assist", "assume", "asthma", "athlete", "atom", "attack", "attend", "attitude", "attract", "auction",
		"audit", "august", "aunt", "author", "auto", "autumn", "average", "avocado", "avoid", "awake", "aware", "away", "awesome", "awful", "awkward", "axis"
};

const char bip39_words_b[117][10] = {
		"baby", "bachelor", "bacon", "badge", "bag", "balance", "balcony", "ball", "bamboo", "banana", "banner", "bar", "barely", "bargain",
		"barrel", "base", "basic", "basket", "battle", "beach", "bean", "beauty", "because", "become", "beef", "before", "begin", "behave",
		"behind", "believe", "below", "belt", "bench", "benefit", "best", "betray", "better", "between", "beyond", "bicycle", "bid", "bike",
		"bind", "biology", "bird", "birth", "bitter", "black", "blade", "blame", "blanket", "blast", "bleak", "bless", "blind", "blood",
		"blossom", "blouse", "blue", "blur", "blush", "board", "boat", "body", "boil", "bomb", "bone", "bonus", "book", "boost", "border", "boring",
		"borrow", "boss", "bottom", "bounce", "box", "boy", "bracket", "brain", "brand", "brass", "brave", "bread", "breeze", "brick",
		"bridge", "brief", "bright", "bring", "brisk", "broccoli", "broken", "bronze", "broom", "brother", "brown", "brush", "bubble", "buddy",
		"budget", "buffalo", "build", "bulb", "bulk", "bullet", "bundle", "bunker", "burden", "burger", "burst", "bus", "business", "busy", "butter", "buyer", "buzz"
};

const char bip39_words_c[186][10] = {
		"cabbage", "cabin", "cable", "cactus", "cage", "cake", "call", "calm", "camera", "camp", "can", "canal", "cancel", "candy",
		"cannon", "canoe", "canvas", "canyon", "capable", "capital", "captain", "car", "carbon", "card", "cargo", "carpet", "carry",
		"cart", "case", "cash", "casino", "castle", "casual", "cat", "catalog", "catch", "category", "cattle", "caught", "cause",
		"caution", "cave", "ceiling", "celery", "cement", "census", "century", "cereal", "certain", "chair", "chalk", "champion",
		"change", "chaos", "chapter", "charge", "chase", "chat", "cheap", "check", "cheese", "chef", "cherry", "chest", "chicken", "chief",
		"child", "chimney", "choice", "choose", "chronic", "chuckle", "chunk", "churn", "cigar", "cinnamon", "circle", "citizen",
		"city", "civil", "claim", "clap", "clarify", "claw", "clay", "clean", "clerk", "clever", "click", "client", "cliff", "climb",
		"clinic", "clip", "clock", "clog", "close", "cloth", "cloud", "clown", "club", "clump", "cluster", "clutch", "coach", "coast",
		"coconut", "code", "coffee", "coil", "coin", "collect", "color", "column", "combine", "come", "comfort", "comic", "common",
		"company", "concert", "conduct", "confirm", "congress", "connect", "consider", "control", "convince", "cook", "cool", "copper", "copy",
		"coral", "core", "corn", "correct", "cost", "cotton", "couch", "country", "couple", "course", "cousin", "cover", "coyote", "crack",
		"cradle", "craft", "cram", "crane", "crash", "crater", "crawl", "crazy", "cream", "credit", "creek", "crew", "cricket", "crime",
		"crisp", "critic", "crop", "cross", "crouch", "crowd", "crucial", "cruel", "cruise", "crumble", "crunch", "crush", "cry", "crystal",
		"cube", "culture", "cup", "cupboard", "curious", "current", "curtain", "curve", "cushion", "custom", "cute", "cycle"
};

const char bip39_words_d[112][10] = {
		"dad", "damage", "damp", "dance", "danger", "daring", "dash", "daughter", "dawn", "day", "deal", "debate", "debris", "decade",
		"december", "decide", "decline", "decorate", "decrease", "deer", "defense", "define", "defy", "degree", "delay", "deliver", "demand",
		"demise", "denial", "dentist", "deny", "depart", "depend", "deposit", "depth", "deputy", "derive", "describe", "desert", "design", "desk",
		"despair", "destroy", "detail", "detect", "develop", "device", "devote", "diagram", "dial", "diamond", "diary", "dice", "diesel", "diet",
		"differ", "digital", "dignity", "dilemma", "dinner", "dinosaur", "direct", "dirt", "disagree", "discover", "disease", "dish", "dismiss",
		"disorder", "display", "distance", "divert", "divide", "divorce", "dizzy", "doctor", "document", "dog", "doll", "dolphin", "domain",
		"donate", "donkey", "donor", "door", "dose", "double", "dove", "draft", "dragon", "drama", "drastic", "draw", "dream", "dress", "drift", "drill",
		"drink", "drip", "drive", "drop", "drum", "dry", "duck", "dumb", "dune", "during", "dust", "dutch", "duty", "dwarf", "dynamic"
};

const char bip39_words_e[100][10] = {
		"eager", "eagle", "early", "earn", "earth", "easily", "east", "easy", "echo", "ecology", "economy", "edge", "edit", "educate",
		"effort", "egg", "eight", "either", "elbow", "elder", "electric", "elegant", "element", "elephant", "elevator", "elite", "else",
		"embark", "embody", "embrace", "emerge", "emotion", "employ", "empower", "empty", "enable", "enact", "end", "endless", "endorse",
		"enemy", "energy", "enforce", "engage", "engine", "enhance", "enjoy", "enlist", "enough", "enrich", "enroll", "ensure", "enter", "entire",
		"entry", "envelope", "episode", "equal", "equip", "era", "erase", "erode", "erosion", "error", "erupt", "escape", "essay", "essence",
		"estate", "eternal", "ethics", "evidence", "evil", "evoke", "evolve", "exact", "example", "excess", "exchange", "excite", "exclude",
		"excuse", "execute", "exercise", "exhaust", "exhibit", "exile", "exist", "exit", "exotic", "expand", "expect", "expire", "explain",
		"expose", "express", "extend", "extra", "eye", "eyebrow"
};

const char bip39_words_f[106][10] = {
		"fabric", "face", "faculty", "fade", "faint", "faith", "fall", "false", "fame", "family", "famous", "fan", "fancy", "fantasy",
		"farm", "fashion", "fat", "fatal", "father", "fatigue", "fault", "favorite", "feature", "february", "federal", "fee", "feed",
		"feel", "female", "fence", "festival", "fetch", "fever", "few", "fiber", "fiction", "field", "figure", "file", "film", "filter",
		"final", "find", "fine", "finger", "finish", "fire", "firm", "first", "fiscal", "fish", "fit", "fitness", "fix", "flag", "flame",
		"flash", "flat", "flavor", "flee", "flight", "flip", "float", "flock", "floor", "flower", "fluid", "flush", "fly", "foam", "focus",
		"fog", "foil", "fold", "follow", "food", "foot", "force", "forest", "forget", "fork", "fortune", "forum", "forward", "fossil", "foster",
		"found", "fox", "fragile", "frame", "frequent", "fresh", "friend", "fringe", "frog", "front", "frost", "frown", "frozen", "fruit",
		"fuel", "fun", "funny", "furnace", "fury", "future"
};

const char bip39_words_g[76][10] = {
		"gadget", "gain", "galaxy", "gallery", "game", "gap", "garage", "garbage", "garden", "garlic", "garment", "gas", "gasp", "gate", "gather", "gauge",
		"gaze", "general", "genius", "genre", "gentle", "genuine", "gesture", "ghost", "giant", "gift", "giggle", "ginger", "giraffe", "girl", "give",
		"glad", "glance", "glare", "glass", "glide", "glimpse", "globe", "gloom", "glory", "glove", "glow", "glue", "goat", "goddess", "gold", "good",
		"goose", "gorilla", "gospel", "gossip", "govern", "gown", "grab", "grace", "grain", "grant", "grape", "grass", "gravity", "great", "green", "grid",
		"grief", "grit", "grocery", "group", "grow", "grunt", "guard", "guess", "guide", "guilt", "guitar", "gun", "gym"
};

const char bip39_words_h[64][10] = {
		"habit", "hair", "half", "hammer", "hamster", "hand", "happy", "harbor", "hard", "harsh", "harvest", "hat", "have", "hawk", "hazard", "head",
		"health", "heart", "heavy", "hedgehog", "height", "hello", "helmet", "help", "hen", "hero", "hidden", "high", "hill", "hint", "hip", "hire",
		"history", "hobby", "hockey", "hold", "hole", "holiday", "hollow", "home", "honey", "hood", "hope", "horn", "horror", "horse", "hospital",
		"host", "hotel", "hour", "hover", "hub", "huge", "human", "humble", "humor", "hundred", "hungry", "hunt", "hurdle", "hurry", "hurt", "husband", "hybrid"
};

const char bip39_words_i[55][10] = {
		"ice", "icon", "idea", "identify", "idle", "ignore", "ill", "illegal", "illness", "image", "imitate", "immense", "immune", "impact", "impose",
		"improve", "impulse", "inch", "include", "income", "increase", "index", "indicate", "indoor", "industry", "infant", "inflict", "inform", "inhale",
		"inherit", "initial", "inject", "injury", "inmate", "inner", "innocent", "input", "inquiry", "insane", "insect", "inside", "inspire", "install",
		"intact", "interest", "into", "invest", "invite", "involve", "iron", "island", "isolate", "issue", "item", "ivory"
};

const char bip39_words_j[20][10] = {
		"jacket", "jaguar", "jar", "jazz", "jealous", "jeans", "jelly", "jewel", "job", "join", "joke", "journey", "joy", "judge", "juice", "jump", "jungle", "junior", "junk", "just"
};

const char bip39_words_k[20][10] = {
		"kangaroo", "keen", "keep", "ketchup", "key", "kick", "kid", "kidney", "kind", "kingdom", "kiss", "kit", "kitchen", "kite", "kitten", "kiwi", "knee", "knife", "knock", "know"
};

const char bip39_words_l[76][10] = {
		"lab", "label", "labor", "ladder", "lady", "lake", "lamp", "language", "laptop", "large", "later", "latin", "laugh", "laundry", "lava", "law",
		"lawn", "lawsuit", "layer", "lazy", "leader", "leaf", "learn", "leave", "lecture", "left", "leg", "legal", "legend", "leisure", "lemon", "lend",
		"length", "lens", "leopard", "lesson", "letter", "level", "liar", "liberty", "library", "license", "life", "lift", "light", "like", "limb",
		"limit", "link", "lion", "liquid", "list", "little", "live", "lizard", "load", "loan", "lobster", "local", "lock", "logic", "lonely", "long",
		"loop", "lottery", "loud", "lounge", "love", "loyal", "lucky", "luggage", "lumber", "lunar", "lunch", "luxury", "lyrics"
};

const char bip39_words_m[105][10] = {
		"machine", "mad", "magic", "magnet", "maid", "mail", "main", "major", "make", "mammal", "man", "manage", "mandate", "mango", "mansion", "manual",
		"maple", "marble", "march", "margin", "marine", "market", "marriage", "mask", "mass", "master", "match", "material", "math", "matrix", "matter", "maximum",
		"maze", "meadow", "mean", "measure", "meat", "mechanic", "medal", "media", "melody", "melt", "member", "memory", "mention", "menu", "mercy", "merge",
		"merit", "merry", "mesh", "message", "metal", "method", "middle", "midnight", "milk", "million", "mimic", "mind", "minimum", "minor", "minute", "miracle",
		"mirror", "misery", "miss", "mistake", "mix", "mixed", "mixture", "mobile", "model", "modify", "mom", "moment", "monitor", "monkey", "monster", "month",
		"moon", "moral", "more", "morning", "mosquito", "mother", "motion", "motor", "mountain", "mouse", "move", "movie", "much", "muffin", "mule", "multiply",
		"muscle", "museum", "mushroom", "music", "must", "mutual", "myself", "mystery", "myth"
};

const char bip39_words_n[41][10] = {
		"naive", "name", "napkin", "narrow", "nasty", "nation", "nature", "near", "neck", "need", "negative", "neglect", "neither", "nephew", "nerve", "nest",
		"net", "network", "neutral", "never", "news", "next", "nice", "night", "noble", "noise", "nominee", "noodle", "normal", "north", "nose", "notable", "note",
		"nothing", "notice", "novel", "now", "nuclear", "number", "nurse", "nut"
};

const char bip39_words_o[55][10] = {
		"oak", "obey", "object", "oblige", "obscure", "observe", "obtain", "obvious", "occur", "ocean", "october", "odor", "off", "offer", "office", "often", "oil",
		"okay", "old", "olive", "olympic", "omit", "once", "one", "onion", "online", "only", "open", "opera", "opinion", "oppose", "option", "orange", "orbit",
		"orchard", "order", "ordinary", "organ", "orient", "original", "orphan", "ostrich", "other", "outdoor", "outer", "output", "outside", "oval", "oven",
		"over", "own", "owner", "oxygen", "oyster", "ozone"
};

const char bip39_words_p[132][10] = {
		"pact", "paddle", "page", "pair", "palace", "palm", "panda", "panel", "panic", "panther", "paper", "parade", "parent", "park", "parrot", "party", "pass", "patch", "path", "patient",
		"patrol", "pattern", "pause", "pave", "payment", "peace", "peanut", "pear", "peasant", "pelican", "pen", "penalty", "pencil", "people", "pepper", "perfect", "permit", "person", "pet", "phone",
		"photo", "phrase", "physical", "piano", "picnic", "picture", "piece", "pig", "pigeon", "pill", "pilot", "pink", "pioneer", "pipe", "pistol", "pitch", "pizza", "place", "planet", "plastic",
		"plate", "play", "please", "pledge", "pluck", "plug", "plunge", "poem", "poet", "point", "polar", "pole", "police", "pond", "pony", "pool", "popular", "portion", "position", "possible",
		"post", "potato", "pottery", "poverty", "powder", "power", "practice", "praise", "predict", "prefer", "prepare", "present", "pretty", "prevent", "price", "pride", "primary", "print", "priority", "prison",
		"private", "prize", "problem", "process", "produce", "profit", "program", "project", "promote", "proof", "property", "prosper", "protect", "proud", "provide", "public", "pudding", "pull", "pulp", "pulse",
		"pumpkin", "punch", "pupil", "puppy", "purchase", "purity", "purpose", "purse", "push", "put", "puzzle", "pyramid"
};

const char bip39_words_q[8][10] = {
		"quality", "quantum", "quarter", "question", "quick", "quit", "quiz", "quote"
};

const char bip39_words_r[108][10] = {
		"rabbit", "raccoon", "race", "rack", "radar", "radio", "rail", "rain", "raise", "rally", "ramp", "ranch", "random", "range", "rapid", "rare", "rate", "rather", "raven", "raw",
		"razor", "ready", "real", "reason", "rebel", "rebuild", "recall", "receive", "recipe", "record", "recycle", "reduce", "reflect", "reform", "refuse", "region", "regret", "regular",
		"reject", "relax", "release", "relief", "rely", "remain", "remember", "remind", "remove", "render", "renew", "rent", "reopen", "repair", "repeat", "replace", "report", "require",
		"rescue", "resemble", "resist", "resource", "response", "result", "retire", "retreat", "return", "reunion", "reveal", "review", "reward", "rhythm", "rib", "ribbon", "rice",
		"rich", "ride", "ridge", "rifle", "right", "rigid", "ring", "riot", "ripple", "risk", "ritual", "rival", "river", "road", "roast", "robot", "robust", "rocket", "romance",
		"roof", "rookie", "room", "rose", "rotate", "rough", "round", "route", "royal", "rubber", "rude", "rug", "rule", "run", "runway", "rural"
};

const char bip39_words_s[250][10] = {
		"sad", "saddle", "sadness", "safe", "sail", "salad", "salmon", "salon", "salt", "salute", "same", "sample", "sand", "satisfy", "satoshi", "sauce", "sausage", "save", "say", "scale",
		"scan", "scare", "scatter", "scene", "scheme", "school", "science", "scissors", "scorpion", "scout", "scrap", "screen", "script", "scrub", "sea", "search", "season", "seat", "second", "secret",
		"section", "security", "seed", "seek", "segment", "select", "sell", "seminar", "senior", "sense", "sentence", "series", "service", "session", "settle", "setup", "seven", "shadow", "shaft", "shallow",
		"share", "shed", "shell", "sheriff", "shield", "shift", "shine", "ship", "shiver", "shock", "shoe", "shoot", "shop", "short", "shoulder", "shove", "shrimp", "shrug", "shuffle", "shy",
		"sibling", "sick", "side", "siege", "sight", "sign", "silent", "silk", "silly", "silver", "similar", "simple", "since", "sing", "siren", "sister", "situate", "six", "size", "skate",
		"sketch", "ski", "skill", "skin", "skirt", "skull", "slab", "slam", "sleep", "slender", "slice", "slide", "slight", "slim", "slogan", "slot", "slow", "slush", "small", "smart",
		"smile", "smoke", "smooth", "snack", "snake", "snap", "sniff", "snow", "soap", "soccer", "social", "sock", "soda", "soft", "solar", "soldier", "solid", "solution", "solve", "someone",
		"song", "soon", "sorry", "sort", "soul", "sound", "soup", "source", "south", "space", "spare", "spatial", "spawn", "speak", "special", "speed", "spell", "spend", "sphere", "spice",
		"spider", "spike", "spin", "spirit", "split", "spoil", "sponsor", "spoon", "sport", "spot", "spray", "spread", "spring", "spy", "square", "squeeze", "squirrel", "stable", "stadium", "staff",
		"stage", "stairs", "stamp", "stand", "start", "state", "stay", "steak", "steel", "stem", "step", "stereo", "stick", "still", "sting", "stock", "stomach", "stone", "stool", "story",
		"stove", "strategy", "street", "strike", "strong", "struggle", "student", "stuff", "stumble", "style", "subject", "submit", "subway", "success", "such", "sudden", "suffer", "sugar", "suggest", "suit",
		"summer", "sun", "sunny", "sunset", "super", "supply", "supreme", "sure", "surface", "surge", "surprise", "surround", "survey", "suspect", "sustain", "swallow", "swamp", "swap", "swarm", "swear",
		"sweet", "swift", "swim", "swing", "switch", "sword", "symbol", "symptom", "syrup", "system"
};

const char bip39_words_t[121][10] = {
		"table", "tackle", "tag", "tail", "talent", "talk", "tank", "tape", "target", "task", "taste", "tattoo", "taxi", "teach", "team", "tell", "ten", "tenant", "tennis", "tent",
		"term", "test", "text", "thank", "that", "theme", "then", "theory", "there", "they", "thing", "this", "thought", "three", "thrive", "throw", "thumb", "thunder", "ticket",
		"tide", "tiger", "tilt", "timber", "time", "tiny", "tip", "tired", "tissue", "title", "toast", "tobacco", "today", "toddler", "toe", "together", "toilet", "token", "tomato",
		"tomorrow", "tone", "tongue", "tonight", "tool", "tooth", "top", "topic", "topple", "torch", "tornado", "tortoise", "toss", "total", "tourist", "toward", "tower", "town",
		"toy", "track", "trade", "traffic", "tragic", "train", "transfer", "trap", "trash", "travel", "tray", "treat", "tree", "trend", "trial", "tribe", "trick", "trigger",
		"trim", "trip", "trophy", "trouble", "truck", "true", "truly", "trumpet", "trust", "truth", "try", "tube", "tuition", "tumble", "tuna", "tunnel", "turkey", "turn",
		"turtle", "twelve", "twenty", "twice", "twin", "twist", "two", "type", "typical"
};

const char bip39_words_u[35][10] = {
		"ugly", "umbrella", "unable", "unaware", "uncle", "uncover", "under", "undo", "unfair", "unfold", "unhappy", "uniform", "unique", "unit", "universe", "unknown", "unlock", "until",
		"unusual", "unveil", "update", "upgrade", "uphold", "upon", "upper", "upset", "urban", "urge", "usage", "use", "used", "useful", "useless", "usual", "utility"
};

const char bip39_words_v[46][10] = {
		"vacant", "vacuum", "vague", "valid", "valley", "valve", "van", "vanish", "vapor", "various", "vast", "vault", "vehicle", "velvet", "vendor", "venture", "venue", "verb", "verify", "version",
		"very", "vessel", "veteran", "viable", "vibrant", "vicious", "victory", "video", "view", "village", "vintage", "violin", "virtual", "virus", "visa", "visit", "visual", "vital", "vivid", "vocal",
		"voice", "void", "volcano", "volume", "vote", "voyage"
};

const char bip39_words_w[69][10] = {
		"wage", "wagon", "wait", "walk", "wall", "walnut", "want", "warfare", "warm", "warrior", "wash", "wasp", "waste", "water", "wave", "way", "wealth", "weapon", "wear", "weasel",
		"weather", "web", "wedding", "weekend", "weird", "welcome", "west", "wet", "whale", "what", "wheat", "wheel", "when", "where", "whip", "whisper", "wide", "width", "wife",
		"wild", "will", "win", "window", "wine", "wing", "wink", "winner", "winter", "wire", "wisdom", "wise", "wish", "witness", "wolf", "woman", "wonder", "wood", "wool", "word",
		"work", "world", "worry", "worth", "wrap", "wreck", "wrestle", "wrist", "write", "wrong"
};

const char bip39_words_y[6][10] = {
		"yard", "year", "yellow", "you", "young", "youth"
};

const char bip39_words_z[4][10] = {
		"zebra", "zero", "zone", "zoo"
};

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
bool getBip39Word(char *word_to_predict)
{
	switch(word_to_predict[0])
	{
	case 'a':
		for(int i=0; i<sizeof(bip39_words_a)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_a[i][0]) && (word_to_predict[1] == bip39_words_a[i][1]) && (word_to_predict[2] == bip39_words_a[i][2]) && (word_to_predict[3] == bip39_words_a[i][3])){
				memcpy(word_to_predict, bip39_words_a[i], 10);
				return true;
			}
		}
		break;

	case 'b':
		for(int i=0; i<sizeof(bip39_words_b)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_b[i][0]) && (word_to_predict[1] == bip39_words_b[i][1]) && (word_to_predict[2] == bip39_words_b[i][2]) && (word_to_predict[3] == bip39_words_b[i][3])){
				memcpy(word_to_predict, bip39_words_b[i], 10);
				return true;
			}
		}
		break;

	case 'c':
		for(int i=0; i<sizeof(bip39_words_c)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_c[i][0]) && (word_to_predict[1] == bip39_words_c[i][1]) && (word_to_predict[2] == bip39_words_c[i][2]) && (word_to_predict[3] == bip39_words_c[i][3])){
				memcpy(word_to_predict, bip39_words_c[i], 10);
				return true;
			}
		}
		break;

	case 'd':
		for(int i=0; i<sizeof(bip39_words_d)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_d[i][0]) && (word_to_predict[1] == bip39_words_d[i][1]) && (word_to_predict[2] == bip39_words_d[i][2]) && (word_to_predict[3] == bip39_words_d[i][3])){
				memcpy(word_to_predict, bip39_words_d[i], 10);
				return true;
			}
		}
		break;

	case 'e':
		for(int i=0; i<sizeof(bip39_words_e)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_e[i][0]) && (word_to_predict[1] == bip39_words_e[i][1]) && (word_to_predict[2] == bip39_words_e[i][2]) && (word_to_predict[3] == bip39_words_e[i][3])){
				memcpy(word_to_predict, bip39_words_e[i], 10);
				return true;
			}
		}
		break;

	case 'f':
		for(int i=0; i<sizeof(bip39_words_f)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_f[i][0]) && (word_to_predict[1] == bip39_words_f[i][1]) && (word_to_predict[2] == bip39_words_f[i][2]) && (word_to_predict[3] == bip39_words_f[i][3])){
				memcpy(word_to_predict, bip39_words_f[i], 10);
				return true;
			}
		}
		break;

	case 'g':
		for(int i=0; i<sizeof(bip39_words_g)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_g[i][0]) && (word_to_predict[1] == bip39_words_g[i][1]) && (word_to_predict[2] == bip39_words_g[i][2]) && (word_to_predict[3] == bip39_words_g[i][3])){
				memcpy(word_to_predict, bip39_words_g[i], 10);
				return true;
			}
		}
		break;

	case 'h':
		for(int i=0; i<sizeof(bip39_words_h)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_h[i][0]) && (word_to_predict[1] == bip39_words_h[i][1]) && (word_to_predict[2] == bip39_words_h[i][2]) && (word_to_predict[3] == bip39_words_h[i][3])){
				memcpy(word_to_predict, bip39_words_h[i], 10);
				return true;
			}
		}
		break;

	case 'i':
		for(int i=0; i<sizeof(bip39_words_i)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_i[i][0]) && (word_to_predict[1] == bip39_words_i[i][1]) && (word_to_predict[2] == bip39_words_i[i][2]) && (word_to_predict[3] == bip39_words_i[i][3])){
				memcpy(word_to_predict, bip39_words_i[i], 10);
				return true;
			}
		}
		break;

	case 'j':
		for(int i=0; i<sizeof(bip39_words_j)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_j[i][0]) && (word_to_predict[1] == bip39_words_j[i][1]) && (word_to_predict[2] == bip39_words_j[i][2]) && (word_to_predict[3] == bip39_words_j[i][3])){
				memcpy(word_to_predict, bip39_words_j[i], 10);
				return true;
			}
		}
		break;

	case 'k':
		for(int i=0; i<sizeof(bip39_words_k)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_k[i][0]) && (word_to_predict[1] == bip39_words_k[i][1]) && (word_to_predict[2] == bip39_words_k[i][2]) && (word_to_predict[3] == bip39_words_k[i][3])){
				memcpy(word_to_predict, bip39_words_k[i], 10);
				return true;
			}
		}
		break;

	case 'l':
		for(int i=0; i<sizeof(bip39_words_l)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_l[i][0]) && (word_to_predict[1] == bip39_words_l[i][1]) && (word_to_predict[2] == bip39_words_l[i][2]) && (word_to_predict[3] == bip39_words_l[i][3])){
				memcpy(word_to_predict, bip39_words_l[i], 10);
				return true;
			}
		}
		break;

	case 'm':
		for(int i=0; i<sizeof(bip39_words_m)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_m[i][0]) && (word_to_predict[1] == bip39_words_m[i][1]) && (word_to_predict[2] == bip39_words_m[i][2]) && (word_to_predict[3] == bip39_words_m[i][3])){
				memcpy(word_to_predict, bip39_words_m[i], 10);
				return true;
			}
		}
		break;

	case 'n':
		for(int i=0; i<sizeof(bip39_words_n)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_n[i][0]) && (word_to_predict[1] == bip39_words_n[i][1]) && (word_to_predict[2] == bip39_words_n[i][2]) && (word_to_predict[3] == bip39_words_n[i][3])){
				memcpy(word_to_predict, bip39_words_n[i], 10);
				return true;
			}
		}
		break;

	case 'o':
		for(int i=0; i<sizeof(bip39_words_o)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_o[i][0]) && (word_to_predict[1] == bip39_words_o[i][1]) && (word_to_predict[2] == bip39_words_o[i][2]) && (word_to_predict[3] == bip39_words_o[i][3])){
				memcpy(word_to_predict, bip39_words_o[i], 10);
				return true;
			}
		}
		break;

	case 'p':
		for(int i=0; i<sizeof(bip39_words_p)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_p[i][0]) && (word_to_predict[1] == bip39_words_p[i][1]) && (word_to_predict[2] == bip39_words_p[i][2]) && (word_to_predict[3] == bip39_words_p[i][3])){
				memcpy(word_to_predict, bip39_words_p[i], 10);
				return true;
			}
		}
		break;

	case 'q':
		for(int i=0; i<sizeof(bip39_words_q)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_q[i][0]) && (word_to_predict[1] == bip39_words_q[i][1]) && (word_to_predict[2] == bip39_words_q[i][2]) && (word_to_predict[3] == bip39_words_q[i][3])){
				memcpy(word_to_predict, bip39_words_q[i], 10);
				return true;
			}
		}
		break;

	case 'r':
		for(int i=0; i<sizeof(bip39_words_r)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_r[i][0]) && (word_to_predict[1] == bip39_words_r[i][1]) && (word_to_predict[2] == bip39_words_r[i][2]) && (word_to_predict[3] == bip39_words_r[i][3])){
				memcpy(word_to_predict, bip39_words_r[i], 10);
				return true;
			}
		}
		break;

	case 's':
		for(int i=0; i<sizeof(bip39_words_s)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_s[i][0]) && (word_to_predict[1] == bip39_words_s[i][1]) && (word_to_predict[2] == bip39_words_s[i][2]) && (word_to_predict[3] == bip39_words_s[i][3])){
				memcpy(word_to_predict, bip39_words_s[i], 10);
				return true;
			}
		}
		break;

	case 't':
		for(int i=0; i<sizeof(bip39_words_t)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_t[i][0]) && (word_to_predict[1] == bip39_words_t[i][1]) && (word_to_predict[2] == bip39_words_t[i][2]) && (word_to_predict[3] == bip39_words_t[i][3])){
				memcpy(word_to_predict, bip39_words_t[i], 10);
				return true;
			}
		}
		break;

	case 'u':
		for(int i=0; i<sizeof(bip39_words_u)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_u[i][0]) && (word_to_predict[1] == bip39_words_u[i][1]) && (word_to_predict[2] == bip39_words_u[i][2]) && (word_to_predict[3] == bip39_words_u[i][3])){
				memcpy(word_to_predict, bip39_words_u[i], 10);
				return true;
			}
		}
		break;

	case 'v':
		for(int i=0; i<sizeof(bip39_words_v)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_v[i][0]) && (word_to_predict[1] == bip39_words_v[i][1]) && (word_to_predict[2] == bip39_words_v[i][2]) && (word_to_predict[3] == bip39_words_v[i][3])){
				memcpy(word_to_predict, bip39_words_v[i], 10);
				return true;
			}
		}
		break;

	case 'w':
		for(int i=0; i<sizeof(bip39_words_w)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_w[i][0]) && (word_to_predict[1] == bip39_words_w[i][1]) && (word_to_predict[2] == bip39_words_w[i][2]) && (word_to_predict[3] == bip39_words_w[i][3])){
				memcpy(word_to_predict, bip39_words_w[i], 10);
				return true;
			}
		}
		break;

	case 'y':
		for(int i=0; i<sizeof(bip39_words_y)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_y[i][0]) && (word_to_predict[1] == bip39_words_y[i][1]) && (word_to_predict[2] == bip39_words_y[i][2]) && (word_to_predict[3] == bip39_words_y[i][3])){
				memcpy(word_to_predict, bip39_words_y[i], 10);
				return true;
			}
		}
		break;

	case 'z':
		for(int i=0; i<sizeof(bip39_words_z)/10; i++)
		{
			if((word_to_predict[0] == bip39_words_z[i][0]) && (word_to_predict[1] == bip39_words_z[i][1]) && (word_to_predict[2] == bip39_words_z[i][2]) && (word_to_predict[3] == bip39_words_z[i][3])){
				memcpy(word_to_predict, bip39_words_z[i], 10);
				return true;
			}
		}
		break;

	default:
	case 'x':
		break;

	}

	return false;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
bool getBip39WordFromGlobalIndex(int index, char *word)
{
	if(index < 136)	 		//'a'
	{
		memcpy(word, bip39_words_a[index], 10);
		return true;
	}
	else if(index < 253)	//'b'
	{
		memcpy(word, bip39_words_b[index-136], 10);
		return true;
	}
	else if(index < 439)	//'c'
	{
		memcpy(word, bip39_words_c[index-253], 10);
		return true;
	}
	else if(index < 551)	//'d'
	{
		memcpy(word, bip39_words_d[index-439], 10);
		return true;
	}
	else if(index < 651)	//'e'
	{
		memcpy(word, bip39_words_e[index-551], 10);
		return true;
	}
	else if(index < 757)	//'f'
	{
		memcpy(word, bip39_words_f[index-651], 10);
		return true;
	}
	else if(index < 833)	//'g'
	{
		memcpy(word, bip39_words_g[index-757], 10);
		return true;
	}
	else if(index < 897)	//'h'
	{
		memcpy(word, bip39_words_h[index-833], 10);
		return true;
	}
	else if(index < 952)	//'i'
	{
		memcpy(word, bip39_words_i[index-897], 10);
		return true;
	}
	else if(index < 972)	//'j'
	{
		memcpy(word, bip39_words_j[index-952], 10);
		return true;
	}
	else if(index < 992)	//'k'
	{
		memcpy(word, bip39_words_k[index-972], 10);
		return true;
	}
	else if(index < 1068)	//'l'
	{
		memcpy(word, bip39_words_l[index-992], 10);
		return true;
	}
	else if(index < 1173)	//'m'
	{
		memcpy(word, bip39_words_m[index-1068], 10);
		return true;
	}
	else if(index < 1214)	//'n'
	{
		memcpy(word, bip39_words_n[index-1173], 10);
		return true;
	}
	else if(index < 1269)	//'o'
	{
		memcpy(word, bip39_words_o[index-1214], 10);
		return true;
	}
	else if(index < 1401)	//'p'
	{
		memcpy(word, bip39_words_p[index-1269], 10);
		return true;
	}
	else if(index < 1409)	//'q'
	{
		memcpy(word, bip39_words_q[index-1401], 10);
		return true;
	}
	else if(index < 1517)	//'r'
	{
		memcpy(word, bip39_words_r[index-1409], 10);
		return true;
	}
	else if(index < 1767)	//'s'
	{
		memcpy(word, bip39_words_s[index-1517], 10);
		return true;
	}
	else if(index < 1888)	//'t'
	{
		memcpy(word, bip39_words_t[index-1767], 10);
		return true;
	}
	else if(index < 1923)	//'u'
	{
		memcpy(word, bip39_words_u[index-1888], 10);
		return true;
	}
	else if(index < 1969)	//'v'
	{
		memcpy(word, bip39_words_v[index-1923], 10);
		return true;
	}
	else if(index < 2038)	//'w'
	{
		memcpy(word, bip39_words_w[index-1969], 10);
		return true;
	}
	else if(index < 2044)	//'y'
	{
		memcpy(word, bip39_words_y[index-2038], 10);
		return true;
	}
	else if(index < 2048)	//'z'
	{
		memcpy(word, bip39_words_z[index-2044], 10);
		return true;
	}

	return false;
}




