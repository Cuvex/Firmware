/**
 ******************************************************************************
 * @file           : xmr_lib.c
 * @brief          : Seed xmr library
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

#include "xmr_lib.h"

const char xmr_words_a[140][10] = {
		"abbey", "abducts", "ability", "ablaze", "abnormal", "abort", "abrasive", "absorb", "abyss", "academy", "aces", "aching", "acidic", "acoustic", "acquire", "across", "actress", "acumen", "adapt", "addicted",
		"adept", "adhesive", "adjust", "adopt", "adrenalin", "adult", "adventure", "aerial", "afar", "affair", "afield", "afloat", "afoot", "afraid", "after", "against", "agenda", "aggravate", "agile", "aglow",
		"agnostic", "agony", "agreed", "ahead", "aided", "ailments", "aimless", "airport", "aisle", "ajar", "akin", "alarms", "album", "alchemy", "alerts", "algebra", "alkaline", "alley", "almost", "aloof",
		"alpine", "already", "also", "altitude", "alumni", "always", "amaze", "ambush", "amended", "amidst", "ammo", "amnesty", "among", "ample", "amused", "anchor", "android", "anecdote", "angled", "ankle",
		"annoyed", "answers", "antics", "anvil", "anxiety", "anybody", "apart", "apex", "aphid", "aplomb", "apology", "apply", "apricot", "aptitude", "aquarium", "arbitrary", "archer", "ardent", "arena",
		"argue", "arises", "army", "around", "arrow", "arsenic", "artistic", "ascend", "ashtray", "aside", "asked", "asleep", "aspire", "assorted", "asylum", "athlete", "atlas", "atom", "atrium", "attire",
		"auburn", "auctions", "audio", "august", "aunt", "austere", "autumn", "avatar", "avidly", "avoid", "awakened", "awesome", "awful", "awkward", "awning", "awoken", "axes", "axis", "axle", "aztec", "azure"
};

const char xmr_words_b[80][10] = {
		"baby", "bacon", "badge", "baffles", "bagpipe", "bailed", "bakery", "balding", "bamboo", "banjo", "baptism", "basin", "batch", "bawled", "bays", "because", "beer", "befit", "begun", "behind",
		"being", "below", "bemused", "benches", "berries", "bested", "betting", "bevel", "beware", "beyond", "bias", "bicycle", "bids", "bifocals", "biggest", "bikini", "bimonthly", "binocular", "biology", "biplane",
		"birth", "biscuit", "bite", "biweekly", "blender", "blip", "bluntly", "boat", "bobsled", "bodies", "bogeys", "boil", "boldly", "bomb", "border", "boss", "both", "bounced", "bovine", "bowling",
		"boxes", "boyfriend", "broken", "brunt", "bubble", "buckets", "budget", "buffet", "bugs", "building", "bulb", "bumper", "bunch", "business", "butter", "buying", "buzzer", "bygones", "byline", "bypass"
};

const char xmr_words_c[63][10] = {
		"cabin", "cactus", "cadets", "cafe", "cage", "cajun", "cake", "calamity", "camp", "candy", "casket", "catch", "cause", "cavernous", "cease", "cedar", "ceiling", "cell", "cement", "cent",
		"certain", "chlorine", "chrome", "cider", "cigar", "cinema", "circle", "cistern", "citadel", "civilian", "claim", "click", "clue", "coal", "cobra", "cocoa", "code", "coexist", "coffee",
		"cogs", "cohesive", "coils", "colony", "comb", "cool", "copy", "corrode", "costume", "cottage", "cousin", "cowl", "criminal", "cube", "cucumber", "cuddled", "cuffs", "cuisine", "cunning",
		"cupcake", "custom", "cycling", "cylinder", "cynical"
};

const char xmr_words_d[88][10] = {
		"dabbing", "dads", "daft", "dagger", "daily", "damp", "dangerous", "dapper", "darted", "dash", "dating", "dauntless", "dawn", "daytime", "dazed", "debut", "decay", "dedicated", "deepest", "deftly",
		"degrees", "dehydrate", "deity", "dejected", "delayed", "demonstra", "dented", "deodorant", "depth", "desk", "devoid", "dewdrop", "dexterity", "dialect", "dice", "diet", "different", "digit", "dilute",
		"dime", "dinner", "diode", "diplomat", "directed", "distance", "ditch", "divers", "dizzy", "doctor", "dodge", "does", "dogs", "doing", "dolphin", "domestic", "donuts", "doorway", "dormant",
		"dosage", "dotted", "double", "dove", "down", "dozen", "dreams", "drinks", "drowning", "drunk", "drying", "dual", "dubbed", "duckling", "dude", "duets", "duke", "dullness", "dummy",
		"dunes", "duplex", "duration", "dusted", "duties", "dwarf", "dwelt", "dwindling", "dying", "dynamite", "dyslexic"
};

const char xmr_words_e[75][10] = {
		"each", "eagle", "earth", "easy", "eating", "eavesdrop", "eccentric", "echo", "eclipse", "economics", "ecstatic", "eden", "edgy", "edited", "educated", "eels", "efficient", "eggs", "egotistic", "eight",
		"either", "eject", "elapse", "elbow", "eldest", "eleven", "elite", "elope", "else", "eluded", "emails", "ember", "emerge", "emit", "emotion", "empty", "emulate", "energy", "enforce", "enhanced",
		"enigma", "enjoy", "enlist", "enmity", "enough", "enraged", "ensign", "entrance", "envy", "epoxy", "equip", "erase", "erected", "erosion", "error", "eskimos", "espionage", "essential", "estate",
		"etched", "eternal", "ethics", "etiquette", "evaluate", "evenings", "evicted", "evolved", "examine", "excess", "exhale", "exit", "exotic", "exquisite", "extra", "exult"
};

const char xmr_words_f[71][10] = {
		"fabrics", "factual", "fading", "fainted", "faked", "fall", "family", "fancy", "farming", "fatal", "faulty", "fawns", "faxed", "fazed", "feast", "february", "federal", "feel", "feline", "females",
		"fences", "ferry", "festival", "fetches", "fever", "fewest", "fiat", "fibula", "fictional", "fidget", "fierce", "fifteen", "fight", "films", "firm", "fishing", "fitting", "five", "fixate",
		"fizzle", "fleet", "flippant", "flying", "foamy", "focus", "foes", "foggy", "foiled", "folding", "fonts", "foolish", "fossil", "fountain", "fowls", "foxes", "foyer", "framed", "friendly",
		"frown", "fruit", "frying", "fudge", "fuel", "fugitive", "fully", "fuming", "fungal", "furnished", "fuselage", "future", "fuzzy"
};

const char xmr_words_g[70][10] = {
		"gables", "gadget", "gags", "gained", "galaxy", "gambit", "gang", "gasp", "gather", "gauze", "gave", "gawk", "gaze", "gearbox", "gecko", "geek", "gels", "gemstone", "general", "geometry",
		"germs", "gesture", "getting", "geyser", "ghetto", "ghost", "giant", "giddy", "gifts", "gigantic", "gills", "gimmick", "ginger", "girth", "giving", "glass", "gleeful", "glide", "gnaw",
		"gnome", "goat", "goblet", "godfather", "goes", "goggles", "going", "goldfish", "gone", "goodbye", "gopher", "gorilla", "gossip", "gotten", "gourmet", "governing", "gown", "greater",
		"grunt", "guarded", "guest", "guide", "gulp", "gumball", "guru", "gusts", "gutter", "guys", "gymnast", "gypsy", "gyrate"
};

const char xmr_words_h[62][10] = {
		"habitat", "hacksaw", "haggled", "hairy", "hamburger", "happens", "hashing", "hatchet", "haunted", "having", "hawk", "haystack", "hazard", "hectare", "hedgehog", "heels", "hefty", "height", "hemlock", "hence",
		"heron", "hesitate", "hexagon", "hickory", "hiding", "highway", "hijack", "hiker", "hills", "himself", "hinder", "hippo", "hire", "history", "hitched", "hive", "hoax", "hobby", "hockey", "hoisting",
		"hold", "honked", "hookup", "hope", "hornet", "hospital", "hotel", "hounded", "hover", "howls", "hubcaps", "huddle", "huge", "hull", "humid", "hunter", "hurried", "husband", "huts", "hybrid",
		"hydrogen", "hyper"
};

const char xmr_words_i[51][10] = {
		"iceberg", "icing", "icon", "identity", "idiom", "idled", "idols", "igloo", "ignore", "iguana", "illness", "imagine", "imbalance", "imitate", "impel", "inactive", "inbound", "incur", "industria", "inexact",
		"inflamed", "ingested", "initiate", "injury", "inkling", "inline", "inmate", "innocent", "inorganic", "input", "inquest", "inroads", "insult", "intended", "inundate", "invoke", "inwardly", "ionic", "irate",
		"iris", "irony", "irritate", "island", "isolated", "issued", "italics", "itches", "items", "itinerary", "itself", "ivory"
};

const char xmr_words_j[44][10] = {
		"jabbed", "jackets", "jaded", "jagged", "jailed", "jamming", "january", "jargon", "jaunt", "javelin", "jaws", "jazz", "jeans", "jeers", "jellyfish", "jeopardy", "jerseys", "jester", "jetting", "jewels",
		"jigsaw", "jingle", "jittery", "jive", "jobs", "jockey", "jogger", "joining", "joking", "jolted", "jostle", "journal", "joyous", "jubilee", "judge", "juggled", "juicy", "jukebox", "july", "jump",
		"junk", "jury", "justice", "juvenile"
};

const char xmr_words_k[21][10] = {
		"kangaroo", "karate", "keep", "kennel", "kept", "kernels", "kettle", "keyboard", "kickoff", "kidneys", "king", "kiosk", "kisses", "kitchens", "kiwi", "knapsack",
		"knee", "knife", "knowledge", "knuckle", "koala"
};

const char xmr_words_l[73][10] = {
		"laborator", "ladder", "lagoon", "lair", "lakes", "lamb", "language", "laptop", "large", "last", "later", "launching", "lava", "lawsuit", "layout", "lazy", "lectures", "ledge", "leech", "left",
		"legion", "leisure", "lemon", "lending", "leopard", "lesson", "lettuce", "lexicon", "liar", "library", "licks", "lids", "lied", "lifestyle", "light", "likewise", "lilac", "limits", "linen",
		"lion", "lipstick", "liquid", "listen", "lively", "loaded", "lobster", "locker", "lodge", "lofty", "logic", "loincloth", "long", "looking", "lopped", "lordship", "losing",
		"lottery", "loudly", "love", "lower", "loyal", "lucky", "luggage", "lukewarm", "lullaby", "lumber", "lunar", "lurk", "lush", "luxury", "lymph", "lynx", "lyrics"
};

const char xmr_words_m[66][10] = {
		"macro", "madness", "magically", "mailed", "major", "makeup", "malady", "mammal", "maps", "masterful", "match", "maul", "maverick", "maximum", "mayor", "maze", "meant", "mechanic", "medicate", "meeting",
		"megabyte", "melting", "memoir", "menu", "merger", "mesh", "metro", "mews", "mice", "midst", "mighty", "mime", "mirror", "misery", "mittens", "mixture", "moat", "mobile", "mocked", "mohawk",
		"moisture", "molten", "moment", "money", "moon", "mops", "morsel", "mostly", "motherly", "mouth", "movement", "mowing", "much", "muddy", "muffin", "mugged", "mullet", "mumble", "mundane",
		"muppet", "mural", "musical", "muzzle", "myriad", "mystery", "myth"
};

const char xmr_words_n[58][10] = {
		"nabbing", "nagged", "nail", "names", "nanny", "napkin", "narrate", "nasty", "natural", "nautical", "navy", "nearby", "necklace", "needed", "negative", "neither", "neon", "nephew", "nerves", "nestle",
		"network", "neutral", "never", "newt", "nexus", "nibs", "niche", "niece", "nifty", "nightly", "nimbly", "nineteen", "nirvana", "nitrogen", "nobody", "nocturnal", "nodes", "noises", "nomad", "noodles",
		"northern", "nostril", "noted", "nouns", "novelty", "nowhere", "nozzle", "nuance", "nucleus", "nudged", "nugget", "nuisance", "null", "number", "nuns", "nurse", "nutshell", "nylon"
};

const char xmr_words_o[69][10] = {
		"oaks", "oars", "oasis", "oatmeal", "obedient", "object", "obliged", "obnoxious", "observant", "obtains", "obvious", "occur", "ocean", "october", "odds", "odometer", "offend", "often", "oilfield", "ointment",
		"okay", "older", "olive", "olympics", "omega", "omission", "omnibus", "onboard", "oncoming", "oneself", "ongoing", "onion", "online", "onslaught", "onto", "onward", "oozed", "opacity", "opened", "opposite",
		"optical", "opus", "orange", "orbit", "orchid", "orders", "organs", "origin", "ornament", "orphans", "oscar", "ostrich", "otherwise", "otter", "ouch", "ought", "ounce", "ourselves", "oust", "outbreak",
		"oval", "oven", "owed", "owls", "owner", "oxidant", "oxygen", "oyster", "ozone"
};

const char xmr_words_p[92][10] = {
		"pact", "paddles", "pager", "pairing", "palace", "pamphlet", "pancakes", "paper", "paradise", "pastry", "patio", "pause", "pavements", "pawnshop", "payment", "peaches", "pebbles", "peculiar", "pedantic", "peeled",
		"pegs", "pelican", "pencil", "people", "pepper", "perfect", "pests", "petals", "phase", "pheasants", "phone", "phrases", "physics", "piano", "picked", "pierce", "pigment", "piloted", "pimple", "pinched",
		"pioneer", "pipeline", "pirate", "pistons", "pitched", "pivot", "pixels", "pizza", "playful", "pledge", "pliers", "plotting", "plus", "plywood", "poaching", "pockets", "podcast", "poetry", "point", "poker",
		"polar", "ponies", "pool", "popular", "portents", "possible", "potato", "pouch", "poverty", "powder", "pram", "present", "pride", "problems", "pruned", "prying", "psychic", "public", "puck", "puddle",
		"puffin", "pulp", "pumpkins", "punch", "puppy", "purged", "push", "putty", "puzzled", "pylons", "pyramid", "python"
};

const char xmr_words_q[3][10] = {
		"queen", "quick", "quote"
};

const char xmr_words_r[80][10] = {
		"rabbits", "racetrack", "radar", "rafts", "rage", "railway", "raking", "rally", "ramped", "randomly",
		"rapid", "rarest", "rash", "rated", "ravine", "rays", "razor", "react", "rebel", "recipe",
		"reduce", "reef", "refer", "regular", "reheat", "reinvest", "rejoices", "rekindle", "relic", "remedy",
		"renting", "reorder", "repent", "request", "reruns", "rest", "return", "reunion", "revamp", "rewind",
		"rhino", "rhythm", "ribbon", "richl", "ridges", "rift", "rigid", "rims", "ringing", "riots",
		"ripped", "rising", "ritual", "river", "roared", "robot", "rockets", "rodent", "rogue", "roles",
		"romance", "roomy", "roped", "roster", "rotate", "rounded", "rover", "rowboat", "royal", "ruby",
		"rudely", "ruffled", "rugged", "ruined", "ruling", "rumble", "runway", "rural", "rustled", "ruthless"
};

const char xmr_words_s[141][10] = {
		"sabotage", "sack", "sadness", "safety", "saga", "sailor", "sake", "salads", "sample", "sanity",
		"sapling", "sarcasm", "sash", "satin", "saucepan", "saved", "sawmill", "saxophone", "sayings", "scamper",
		"scenic", "school", "science", "scoop", "scrub", "scuba", "seasons", "second", "sedan", "seeded",
		"segments", "seismic", "selfish", "semifinal", "sensible", "september", "sequence", "serving", "session", "setup",
		"seventh", "sewage", "shackles", "shelter", "shipped", "shocking", "shrugged", "shuffled", "shyness", "siblings",
		"sickness", "sidekick", "sieve", "sifting", "sighting", "silk", "simplest", "sincerely", "sipped", "siren",
		"situated", "sixteen", "sizes", "skater", "skew", "skirting", "skulls", "skydive", "slackens", "sleepless",
		"slid", "slower", "slug", "smash", "smelting", "smidgen", "smog", "smuggled", "snake", "sneeze",
		"sniff", "snout", "snug", "soapy", "sober", "soccer", "soda", "software", "soggy", "soil",
		"solved", "somewhere", "sonic", "soothe", "soprano", "sorry", "southern", "sovereign", "sowed", "soya",
		"space", "speedy", "sphere", "spiders", "splendid", "spout", "sprig", "spud", "spying", "square",
		"stacking", "stellar", "stick", "stockpile", "strained", "stunning", "stylishly", "subtly", "succeed", "suddenly",
		"suede", "suffice", "sugar", "suitcase", "sulking", "summon", "sunken", "superior", "surfer", "sushi",
		"suture", "swagger", "swept", "swiftly", "sword", "swung", "syllabus", "symptoms", "syndrome", "syringe",
		"system"
};

const char xmr_words_t[96][10] = {
		"taboo", "tacit", "tadpoles", "tagged", "tail", "taken", "talent", "tamper", "tanks", "tapestry",
		"tarnished", "tasked", "tattoo", "taunts", "tavern", "tawny", "taxi", "teardrop", "technical", "tedious",
		"teeming", "tell", "template", "tender", "tepid", "tequila", "terminal", "testing", "tether", "textbook",
		"thaw", "theatrics", "thirsty", "thorn", "threaten", "thumbs", "thwart", "ticket", "tidy", "tiers",
		"tiger", "tilt", "timber", "tinted", "tipsy", "tirade", "tissue", "titans", "toaster", "tobacco",
		"today", "toenail", "toffee", "together", "toilet", "token", "tolerant", "tomorrow", "tonic", "toolbox",
		"topic", "torch", "tossed", "total", "touchy", "towel", "toxic", "toyed", "trash", "trendy",
		"tribal", "trolling", "truth", "trying", "tsunami", "tubes", "tucks", "tudor", "tuesday", "tufts",
		"tugs", "tuition", "tulips", "tumbling", "tunnel", "turnip", "tusks", "tutor", "tuxedo", "twang",
		"tweezers", "twice", "twofold", "tycoon", "typist", "tyrant"
};

const char xmr_words_u[55][10] = {
		"ugly", "ulcers", "ultimate", "umbrella", "umpire", "unafraid", "unbending", "uncle", "under", "uneven",
		"unfit", "ungainly", "unhappy", "union", "unjustly", "unknown", "unlikely", "unmask", "unnoticed", "unopened",
		"unplugs", "unquoted", "unrest", "unsafe", "until", "unusual", "unveil", "unwind", "unzip", "upbeat",
		"upcoming", "update", "upgrade", "uphill", "upkeep", "upload", "upon", "upper", "upright", "upstairs",
		"uptight", "upwards", "urban", "urchins", "urgent", "usage", "useful", "usher", "using", "usual",
		"utensils", "utility", "utmost", "utopia", "uttered"
};

const char xmr_words_v[48][10] = {
		"vacation", "vague", "vain", "value", "vampire", "vane", "vapidly", "vary", "vastness", "vats",
		"vaults", "vector", "veered", "vegan", "vehicle", "vein", "velvet", "venomous", "verificat", "vessel",
		"veteran", "vexed", "vials", "vibrate", "victim", "video", "viewpoint", "vigilant", "viking", "village",
		"vinegar", "violin", "vipers", "virtual", "visited", "vitals", "vivid", "vixen", "vocal", "vogue",
		"voice", "volcano", "vortex", "voted", "voucher", "vowels", "voyage", "vulture"
};

const char xmr_words_w[54][10] = {
		"wade", "waffle", "wagtail", "waist", "waking", "wallets", "wanted", "warped", "washing", "water",
		"waveform", "waxing", "wayside", "weavers", "website", "wedge", "weekday", "weird", "welders", "went",
		"wept", "were", "western", "wetsuit", "whale", "when", "whipped", "whole", "wickets", "width",
		"wield", "wife", "wiggle", "wildly", "winter", "wipeout", "wiring", "wise", "withdrawn", "wives",
		"wizard", "wobbly", "woes", "woken", "wolf", "womanly", "wonders", "woozy", "worry", "wounded",
		"woven", "wrap", "wrist", "wrong"
};

const char xmr_words_y[14][10] = {
		"yacht", "yahoo", "yanks", "yard", "yawning", "yearbook", "yellow", "yesterday", "yeti", "yields",
		"yodel", "yoga", "younger", "yoyo"
};

const char xmr_words_z[12][10] = {
		"zapped", "zeal", "zebra", "zero", "zesty", "zigzags", "zinger", "zippers", "zodiac", "zombie",
		"zones", "zoom"
};

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
bool getXmrWord(char *word_to_predict)
{
	switch(word_to_predict[0])
	{
	case 'a':
		for(int i=0; i<sizeof(xmr_words_a)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_a[i][0]) && (word_to_predict[1] == xmr_words_a[i][1]) && (word_to_predict[2] == xmr_words_a[i][2]) && (word_to_predict[3] == xmr_words_a[i][3])){
				memcpy(word_to_predict, xmr_words_a[i], 10);
				return true;
			}
		}
		break;

	case 'b':
		for(int i=0; i<sizeof(xmr_words_b)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_b[i][0]) && (word_to_predict[1] == xmr_words_b[i][1]) && (word_to_predict[2] == xmr_words_b[i][2]) && (word_to_predict[3] == xmr_words_b[i][3])){
				memcpy(word_to_predict, xmr_words_b[i], 10);
				return true;
			}
		}
		break;

	case 'c':
		for(int i=0; i<sizeof(xmr_words_c)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_c[i][0]) && (word_to_predict[1] == xmr_words_c[i][1]) && (word_to_predict[2] == xmr_words_c[i][2]) && (word_to_predict[3] == xmr_words_c[i][3])){
				memcpy(word_to_predict, xmr_words_c[i], 10);
				return true;
			}
		}
		break;

	case 'd':
		for(int i=0; i<sizeof(xmr_words_d)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_d[i][0]) && (word_to_predict[1] == xmr_words_d[i][1]) && (word_to_predict[2] == xmr_words_d[i][2]) && (word_to_predict[3] == xmr_words_d[i][3])){
				memcpy(word_to_predict, xmr_words_d[i], 10);
				return true;
			}
		}
		break;

	case 'e':
		for(int i=0; i<sizeof(xmr_words_e)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_e[i][0]) && (word_to_predict[1] == xmr_words_e[i][1]) && (word_to_predict[2] == xmr_words_e[i][2]) && (word_to_predict[3] == xmr_words_e[i][3])){
				memcpy(word_to_predict, xmr_words_e[i], 10);
				return true;
			}
		}
		break;

	case 'f':
		for(int i=0; i<sizeof(xmr_words_f)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_f[i][0]) && (word_to_predict[1] == xmr_words_f[i][1]) && (word_to_predict[2] == xmr_words_f[i][2]) && (word_to_predict[3] == xmr_words_f[i][3])){
				memcpy(word_to_predict, xmr_words_f[i], 10);
				return true;
			}
		}
		break;

	case 'g':
		for(int i=0; i<sizeof(xmr_words_g)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_g[i][0]) && (word_to_predict[1] == xmr_words_g[i][1]) && (word_to_predict[2] == xmr_words_g[i][2]) && (word_to_predict[3] == xmr_words_g[i][3])){
				memcpy(word_to_predict, xmr_words_g[i], 10);
				return true;
			}
		}
		break;

	case 'h':
		for(int i=0; i<sizeof(xmr_words_h)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_h[i][0]) && (word_to_predict[1] == xmr_words_h[i][1]) && (word_to_predict[2] == xmr_words_h[i][2]) && (word_to_predict[3] == xmr_words_h[i][3])){
				memcpy(word_to_predict, xmr_words_h[i], 10);
				return true;
			}
		}
		break;

	case 'i':
		for(int i=0; i<sizeof(xmr_words_i)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_i[i][0]) && (word_to_predict[1] == xmr_words_i[i][1]) && (word_to_predict[2] == xmr_words_i[i][2]) && (word_to_predict[3] == xmr_words_i[i][3])){
				memcpy(word_to_predict, xmr_words_i[i], 10);
				return true;
			}
		}
		break;

	case 'j':
		for(int i=0; i<sizeof(xmr_words_j)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_j[i][0]) && (word_to_predict[1] == xmr_words_j[i][1]) && (word_to_predict[2] == xmr_words_j[i][2]) && (word_to_predict[3] == xmr_words_j[i][3])){
				memcpy(word_to_predict, xmr_words_j[i], 10);
				return true;
			}
		}
		break;

	case 'k':
		for(int i=0; i<sizeof(xmr_words_k)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_k[i][0]) && (word_to_predict[1] == xmr_words_k[i][1]) && (word_to_predict[2] == xmr_words_k[i][2]) && (word_to_predict[3] == xmr_words_k[i][3])){
				memcpy(word_to_predict, xmr_words_k[i], 10);
				return true;
			}
		}
		break;

	case 'l':
		for(int i=0; i<sizeof(xmr_words_l)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_l[i][0]) && (word_to_predict[1] == xmr_words_l[i][1]) && (word_to_predict[2] == xmr_words_l[i][2]) && (word_to_predict[3] == xmr_words_l[i][3])){
				memcpy(word_to_predict, xmr_words_l[i], 10);
				return true;
			}
		}
		break;

	case 'm':
		for(int i=0; i<sizeof(xmr_words_m)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_m[i][0]) && (word_to_predict[1] == xmr_words_m[i][1]) && (word_to_predict[2] == xmr_words_m[i][2]) && (word_to_predict[3] == xmr_words_m[i][3])){
				memcpy(word_to_predict, xmr_words_m[i], 10);
				return true;
			}
		}
		break;

	case 'n':
		for(int i=0; i<sizeof(xmr_words_n)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_n[i][0]) && (word_to_predict[1] == xmr_words_n[i][1]) && (word_to_predict[2] == xmr_words_n[i][2]) && (word_to_predict[3] == xmr_words_n[i][3])){
				memcpy(word_to_predict, xmr_words_n[i], 10);
				return true;
			}
		}
		break;

	case 'o':
		for(int i=0; i<sizeof(xmr_words_o)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_o[i][0]) && (word_to_predict[1] == xmr_words_o[i][1]) && (word_to_predict[2] == xmr_words_o[i][2]) && (word_to_predict[3] == xmr_words_o[i][3])){
				memcpy(word_to_predict, xmr_words_o[i], 10);
				return true;
			}
		}
		break;

	case 'p':
		for(int i=0; i<sizeof(xmr_words_p)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_p[i][0]) && (word_to_predict[1] == xmr_words_p[i][1]) && (word_to_predict[2] == xmr_words_p[i][2]) && (word_to_predict[3] == xmr_words_p[i][3])){
				memcpy(word_to_predict, xmr_words_p[i], 10);
				return true;
			}
		}
		break;

	case 'q':
		for(int i=0; i<sizeof(xmr_words_q)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_q[i][0]) && (word_to_predict[1] == xmr_words_q[i][1]) && (word_to_predict[2] == xmr_words_q[i][2]) && (word_to_predict[3] == xmr_words_q[i][3])){
				memcpy(word_to_predict, xmr_words_q[i], 10);
				return true;
			}
		}
		break;

	case 'r':
		for(int i=0; i<sizeof(xmr_words_r)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_r[i][0]) && (word_to_predict[1] == xmr_words_r[i][1]) && (word_to_predict[2] == xmr_words_r[i][2]) && (word_to_predict[3] == xmr_words_r[i][3])){
				memcpy(word_to_predict, xmr_words_r[i], 10);
				return true;
			}
		}
		break;

	case 's':
		for(int i=0; i<sizeof(xmr_words_s)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_s[i][0]) && (word_to_predict[1] == xmr_words_s[i][1]) && (word_to_predict[2] == xmr_words_s[i][2]) && (word_to_predict[3] == xmr_words_s[i][3])){
				memcpy(word_to_predict, xmr_words_s[i], 10);
				return true;
			}
		}
		break;

	case 't':
		for(int i=0; i<sizeof(xmr_words_t)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_t[i][0]) && (word_to_predict[1] == xmr_words_t[i][1]) && (word_to_predict[2] == xmr_words_t[i][2]) && (word_to_predict[3] == xmr_words_t[i][3])){
				memcpy(word_to_predict, xmr_words_t[i], 10);
				return true;
			}
		}
		break;

	case 'u':
		for(int i=0; i<sizeof(xmr_words_u)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_u[i][0]) && (word_to_predict[1] == xmr_words_u[i][1]) && (word_to_predict[2] == xmr_words_u[i][2]) && (word_to_predict[3] == xmr_words_u[i][3])){
				memcpy(word_to_predict, xmr_words_u[i], 10);
				return true;
			}
		}
		break;

	case 'v':
		for(int i=0; i<sizeof(xmr_words_v)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_v[i][0]) && (word_to_predict[1] == xmr_words_v[i][1]) && (word_to_predict[2] == xmr_words_v[i][2]) && (word_to_predict[3] == xmr_words_v[i][3])){
				memcpy(word_to_predict, xmr_words_v[i], 10);
				return true;
			}
		}
		break;

	case 'w':
		for(int i=0; i<sizeof(xmr_words_w)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_w[i][0]) && (word_to_predict[1] == xmr_words_w[i][1]) && (word_to_predict[2] == xmr_words_w[i][2]) && (word_to_predict[3] == xmr_words_w[i][3])){
				memcpy(word_to_predict, xmr_words_w[i], 10);
				return true;
			}
		}
		break;

	case 'y':
		for(int i=0; i<sizeof(xmr_words_y)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_y[i][0]) && (word_to_predict[1] == xmr_words_y[i][1]) && (word_to_predict[2] == xmr_words_y[i][2]) && (word_to_predict[3] == xmr_words_y[i][3])){
				memcpy(word_to_predict, xmr_words_y[i], 10);
				return true;
			}
		}
		break;

	case 'z':
		for(int i=0; i<sizeof(xmr_words_z)/10; i++)
		{
			if((word_to_predict[0] == xmr_words_z[i][0]) && (word_to_predict[1] == xmr_words_z[i][1]) && (word_to_predict[2] == xmr_words_z[i][2]) && (word_to_predict[3] == xmr_words_z[i][3])){
				memcpy(word_to_predict, xmr_words_z[i], 10);
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




