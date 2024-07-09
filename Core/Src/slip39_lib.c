/**
 ******************************************************************************
 * @file           : slip39_lib.c
 * @brief          : Seed slip39 library
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

#include "slip39_lib.h"

const char slip39_words_a[67][10] = {
		"academic", "acid", "acne", "acquire", "acrobat", "activity", "actress", "adapt", "adequate", "adjust",
		"admit", "adorn", "adult", "advance", "advocate", "afraid", "again", "agency", "agree", "aide",
		"aircraft", "airline", "airport", "ajar", "alarm", "album", "alcohol", "alien", "alive", "alpha",
		"already", "alto", "aluminum", "always", "amazing", "ambition", "amount", "amuse", "analysis",
		"anatomy", "ancestor", "ancient", "angel", "angry", "animal", "answer", "antenna", "anxiety",
		"apart", "aquatic", "arcade", "arena", "argue", "armed", "artist", "artwork", "aspect", "auction",
		"august", "aunt", "average", "aviation", "avoid", "award", "away", "axis", "axle"
};

const char slip39_words_b[47][10] = {
		"beam", "beard", "beaver", "become", "bedroom", "behavior", "being", "believe", "belong", "benefit",
		"best", "beyond", "bike", "biology", "birthday", "bishop", "black", "blanket", "blessing", "blimp",
		"blind", "blue", "body", "bolt", "boring", "born", "both", "boundary", "bracelet", "branch",
		"brave", "breathe", "briefing", "broken", "brother", "browser", "bucket", "budget", "building",
		"bulb", "bulge", "bumpy", "bundle", "burden", "burning", "busy", "buyer"
};

const char slip39_words_c[71][10] = {
		"cage", "calcium", "camera", "campus", "canyon", "capacity", "capital", "capture", "carbon", "cards",
		"careful", "cargo", "carpet", "carve", "category", "cause", "ceiling", "center", "ceramic", "champion",
		"change", "charity", "check", "chemical", "chest", "chew", "chubby", "cinema", "civil", "class",
		"clay", "cleanup", "client", "climate", "clinic", "clock", "clogs", "closet", "clothes", "club",
		"cluster", "coal", "coastal", "coding", "column", "company", "corner", "costume", "counter", "course",
		"cover", "cowboy", "cradle", "craft", "crazy", "credit", "cricket", "criminal", "crisis", "critical",
		"crowd", "crucial", "crunch", "crush", "crystal", "cubic", "cultural", "curious", "curly", "custody",
		"cylinder"
};

const char slip39_words_d[68][10] = {
		"daisy", "damage", "dance", "darkness", "database", "daughter", "deadline", "deal", "debris", "debut",
		"decent", "decision", "declare", "decorate", "decrease", "deliver", "demand", "density", "deny", "depart",
		"depend", "depict", "deploy", "describe", "desert", "desire", "desktop", "destroy", "detailed", "detect",
		"device", "devote", "diagnose", "dictate", "diet", "dilemma", "diminish", "dining", "diploma", "disaster",
		"discuss", "disease", "dish", "dismiss", "display", "distance", "dive", "divorce", "document", "domain",
		"domestic", "dominant", "dough", "downtown", "dragon", "dramatic", "dream", "dress", "drift", "drink",
		"drove", "drug", "dryer", "duckling", "duke", "duration", "dwarf", "dynamic"
};

const char slip39_words_e[70][10] = {
		"early", "earth", "easel", "easy", "echo", "eclipse", "ecology", "edge", "editor", "educate",
		"either", "elbow", "elder", "election", "elegant", "element", "elephant", "elevator", "elite", "else",
		"email", "emerald", "emission", "emperor", "emphasis", "employer", "empty", "ending", "endless", "endorse",
		"enemy", "energy", "enforce", "engage", "enjoy", "enlarge", "entrance", "envelope", "envy", "epidemic",
		"episode", "equation", "equip", "eraser", "erode", "escape", "estate", "estimate", "evaluate", "evening",
		"evidence", "evil", "evoke", "exact", "example", "exceed", "exchange", "exclude", "excuse", "execute",
		"exercise", "exhaust", "exotic", "expand", "expect", "explain", "express", "extend", "extra", "eyebrow"
};

const char slip39_words_f[58][10] = {
		"facility", "fact", "failure", "faint", "fake", "false", "family", "famous", "fancy", "fangs",
		"fantasy", "fatal", "fatigue", "favorite", "fawn", "fiber", "fiction", "filter", "finance", "findings",
		"finger", "firefly", "firm", "fiscal", "fishing", "fitness", "flame", "flash", "flavor", "flea",
		"flexible", "flip", "float", "floral", "fluff", "focus", "forbid", "force", "forecast", "forget",
		"formal", "fortune", "forward", "founder", "fraction", "fragment", "frequent", "freshman", "friar",
		"fridge", "friendly", "frost", "froth", "frozen", "fumes", "funding", "furl", "fused"
};

const char slip39_words_g[39][10] = {
		"galaxy", "game", "garbage", "garden", "garlic", "gasoline", "gather", "general", "genius", "genre",
		"genuine", "geology", "gesture", "glad", "glance", "glasses", "glen", "glimpse", "goat", "golden",
		"graduate", "grant", "grasp", "gravity", "gray", "greatest", "grief", "grill", "grin", "grocery",
		"gross", "group", "grownup", "grumpy", "guard", "guest", "guilt", "guitar", "gums"
};

const char slip39_words_h[32][10] = {
		"hairy", "hamster", "hand", "hanger", "harvest", "have", "havoc", "hawk", "hazard", "headset",
		"health", "hearing", "heat", "helpful", "herald", "herd", "hesitate", "hobo", "holiday", "holy",
		"home", "hormone", "hospital", "hour", "huge", "human", "humidity", "hunting", "husband", "hush",
		"husky", "hybrid"
};

const char slip39_words_i[31][10] = {
		"idea", "identify", "idle", "image", "impact", "imply", "improve", "impulse", "include", "income",
		"increase", "index", "indicate", "industry", "infant", "inform", "inherit", "injury", "inmate", "insect",
		"inside", "install", "intend", "intimate", "invasion", "involve", "iris", "island", "isolate", "item", "ivory"
};

const char slip39_words_j[12][10] = {
		"jacket", "jerky", "jewelry", "join", "judicial", "juice", "jump", "junction", "junior", "junk", "jury", "justice"
};

const char slip39_words_k[7][10] = {
		"kernel", "keyboard", "kidney", "kind", "kitchen", "knife", "knit"
};

const char slip39_words_l[47][10] = {
		"laden", "ladle", "ladybug", "lair", "lamp", "language", "large", "laser", "laundry", "lawsuit",
		"leader", "leaf", "learn", "leaves", "lecture", "legal", "legend", "legs", "lend", "length",
		"level", "liberty", "library", "license", "lift", "likely", "lilac", "lily", "lips", "liquid",
		"listen", "literary", "living", "lizard", "loan", "lobe", "location", "losing", "loud", "loyalty",
		"luck", "lunar", "lunch", "lungs", "luxury", "lying", "lyrics"
};

const char slip39_words_m[57][10] = {
		"machine", "magazine", "maiden", "mailman", "main", "makeup", "making", "mama", "manager", "mandate",
		"mansion", "manual", "marathon", "march", "market", "marvel", "mason", "material", "math", "maximum",
		"mayor", "meaning", "medal", "medical", "member", "memory", "mental", "merchant", "merit", "method",
		"metric", "midst", "mild", "military", "mineral", "minister", "miracle", "mixed", "mixture", "mobile",
		"modern", "modify", "moisture", "moment", "morning", "mortgage", "mother", "mountain", "mouse", "move",
		"much", "mule", "multiple", "muscle", "museum", "music", "mustang"
};

const char slip39_words_n[11][10] = {
		"nail", "national", "necklace", "negative", "nervous", "network", "news", "nuclear", "numb", "numerous", "nylon"
};

const char slip39_words_o[19][10] = {
		"oasis", "obesity", "object", "observe", "obtain", "ocean", "often", "olympic", "omit", "oral",
		"orange", "orbit", "order", "ordinary", "organize", "ounce", "oven", "overall", "owner"
};

const char slip39_words_p[80][10] = {
		"paces", "pacific", "package", "paid", "painting", "pajamas", "pancake", "pants", "papa", "paper",
		"parcel", "parking", "party", "patent", "patrol", "payment", "payroll", "peaceful", "peanut", "peasant",
		"pecan", "penalty", "pencil", "percent", "perfect", "permit", "petition", "phantom", "pharmacy", "photo",
		"phrase", "physics", "pickup", "picture", "piece", "pile", "pink", "pipeline", "pistol", "pitch",
		"plains", "plan", "plastic", "platform", "playoff", "pleasure", "plot", "plunge", "practice", "prayer",
		"preach", "predator", "pregnant", "premium", "prepare", "presence", "prevent", "priest", "primary", "priority",
		"prisoner", "privacy", "prize", "problem", "process", "profile", "program", "promise", "prospect", "provide",
		"prune", "public", "pulse", "pumps", "punish", "puny", "pupal", "purchase", "purple", "python"
};

const char slip39_words_q[4][10] = {
		"quantity", "quarter", "quick", "quiet"
};

const char slip39_words_r[55][10] = {
		"race", "racism", "radar", "railroad", "rainbow", "raisin", "random", "ranked", "rapids", "raspy",
		"reaction", "realize", "rebound", "rebuild", "recall", "receiver", "recover", "regret", "regular", "reject",
		"relate", "remember", "remind", "remove", "render", "repair", "repeat", "replace", "require", "rescue",
		"research", "resident", "response", "result", "retailer", "retreat", "reunion", "revenue", "review", "reward",
		"rhyme", "rhythm", "rich", "rival", "river", "robin", "rocky", "romantic", "romp", "roster", "round",
		"royal", "ruin", "ruler", "rumor"
};

const char slip39_words_s[115][10] = {
		"sack", "safari", "salary", "salon", "salt", "satisfy", "satoshi", "saver", "says", "scandal",
		"scared", "scatter", "scene", "scholar", "science", "scout", "scramble", "screw", "script", "scroll",
		"seafood", "season", "secret", "security", "segment", "senior", "shadow", "shaft", "shame", "shaped",
		"sharp", "shelter", "sheriff", "short", "should", "shrimp", "sidewalk", "silent", "silver", "similar",
		"simple", "single", "sister", "skin", "skunk", "slap", "slavery", "sled", "slice", "slim", "slow",
		"slush", "smart", "smear", "smell", "smirk", "smith", "smoking", "smug", "snake", "snapshot", "sniff",
		"society", "software", "soldier", "solution", "soul", "source", "space", "spark", "speak", "species",
		"spelling", "spend", "spew", "spider", "spill", "spine", "spirit", "spit", "spray", "sprinkle", "square",
		"squeeze", "stadium", "staff", "standard", "starting", "station", "stay", "steady", "step", "stick",
		"stilt", "story", "strategy", "strike", "style", "subject", "submit", "sugar", "suitable", "sunlight",
		"superior", "surface", "surprise", "survive", "sweater", "swimming", "swing", "switch", "symbolic",
		"sympathy", "syndrome", "system"
};

const char slip39_words_t[56][10] = {
		"tackle", "tactics", "tadpole", "talent", "task", "taste", "taught", "taxi", "teacher", "teammate",
		"teaspoon", "temple", "tenant", "tendency", "tension", "terminal", "testify", "texture", "thank", "that",
		"theater", "theory", "therapy", "thorn", "threaten", "thumb", "thunder", "ticket", "tidy", "timber",
		"timely", "ting", "tofu", "together", "tolerate", "total", "toxic", "tracks", "traffic", "training",
		"transfer", "trash", "traveler", "treat", "trend", "trial", "tricycle", "trip", "triumph", "trouble",
		"true", "trust", "twice", "twin", "type", "typical"
};

const char slip39_words_u[19][10] = {
		"ugly", "ultimate", "umbrella", "uncover", "undergo", "unfair", "unfold", "unhappy", "union", "universe",
		"unkind", "unknown", "unusual", "unwrap", "upgrade", "upstairs", "username", "usher", "usual"
};

const char slip39_words_v[27][10] = {
		"valid", "valuable", "vampire", "vanish", "various", "vegan", "velvet", "venture", "verdict", "verify",
		"very", "veteran", "vexed", "victim", "video", "view", "vintage", "violence", "viral", "visitor",
		"visual", "vitamins", "vocal", "voice", "volume", "voter", "voting"
};

const char slip39_words_w[27][10] = {
		"walnut", "warmth", "warn", "watch", "wavy", "wealthy", "weapon", "webcam", "welcome", "welfare",
		"western", "width", "wildlife", "window", "wine", "wireless", "wisdom", "withdraw", "wits", "wolf",
		"woman", "work", "worthy", "wrap", "wrist", "writing", "wrote"
};

const char slip39_words_y[4][10] = {
		"year", "yelp", "yield", "yoga"
};

const char slip39_words_z[1][10] = {
		"zero"
};

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
bool getSlip39Word(char *word_to_predict)
{
	switch(word_to_predict[0])
	{
	case 'a':
		for(int i=0; i<sizeof(slip39_words_a)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_a[i][0]) && (word_to_predict[1] == slip39_words_a[i][1]) && (word_to_predict[2] == slip39_words_a[i][2]) && (word_to_predict[3] == slip39_words_a[i][3])){
				memcpy(word_to_predict, slip39_words_a[i], 10);
				return true;
			}
		}
		break;

	case 'b':
		for(int i=0; i<sizeof(slip39_words_b)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_b[i][0]) && (word_to_predict[1] == slip39_words_b[i][1]) && (word_to_predict[2] == slip39_words_b[i][2]) && (word_to_predict[3] == slip39_words_b[i][3])){
				memcpy(word_to_predict, slip39_words_b[i], 10);
				return true;
			}
		}
		break;

	case 'c':
		for(int i=0; i<sizeof(slip39_words_c)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_c[i][0]) && (word_to_predict[1] == slip39_words_c[i][1]) && (word_to_predict[2] == slip39_words_c[i][2]) && (word_to_predict[3] == slip39_words_c[i][3])){
				memcpy(word_to_predict, slip39_words_c[i], 10);
				return true;
			}
		}
		break;

	case 'd':
		for(int i=0; i<sizeof(slip39_words_d)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_d[i][0]) && (word_to_predict[1] == slip39_words_d[i][1]) && (word_to_predict[2] == slip39_words_d[i][2]) && (word_to_predict[3] == slip39_words_d[i][3])){
				memcpy(word_to_predict, slip39_words_d[i], 10);
				return true;
			}
		}
		break;

	case 'e':
		for(int i=0; i<sizeof(slip39_words_e)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_e[i][0]) && (word_to_predict[1] == slip39_words_e[i][1]) && (word_to_predict[2] == slip39_words_e[i][2]) && (word_to_predict[3] == slip39_words_e[i][3])){
				memcpy(word_to_predict, slip39_words_e[i], 10);
				return true;
			}
		}
		break;

	case 'f':
		for(int i=0; i<sizeof(slip39_words_f)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_f[i][0]) && (word_to_predict[1] == slip39_words_f[i][1]) && (word_to_predict[2] == slip39_words_f[i][2]) && (word_to_predict[3] == slip39_words_f[i][3])){
				memcpy(word_to_predict, slip39_words_f[i], 10);
				return true;
			}
		}
		break;

	case 'g':
		for(int i=0; i<sizeof(slip39_words_g)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_g[i][0]) && (word_to_predict[1] == slip39_words_g[i][1]) && (word_to_predict[2] == slip39_words_g[i][2]) && (word_to_predict[3] == slip39_words_g[i][3])){
				memcpy(word_to_predict, slip39_words_g[i], 10);
				return true;
			}
		}
		break;

	case 'h':
		for(int i=0; i<sizeof(slip39_words_h)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_h[i][0]) && (word_to_predict[1] == slip39_words_h[i][1]) && (word_to_predict[2] == slip39_words_h[i][2]) && (word_to_predict[3] == slip39_words_h[i][3])){
				memcpy(word_to_predict, slip39_words_h[i], 10);
				return true;
			}
		}
		break;

	case 'i':
		for(int i=0; i<sizeof(slip39_words_i)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_i[i][0]) && (word_to_predict[1] == slip39_words_i[i][1]) && (word_to_predict[2] == slip39_words_i[i][2]) && (word_to_predict[3] == slip39_words_i[i][3])){
				memcpy(word_to_predict, slip39_words_i[i], 10);
				return true;
			}
		}
		break;

	case 'j':
		for(int i=0; i<sizeof(slip39_words_j)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_j[i][0]) && (word_to_predict[1] == slip39_words_j[i][1]) && (word_to_predict[2] == slip39_words_j[i][2]) && (word_to_predict[3] == slip39_words_j[i][3])){
				memcpy(word_to_predict, slip39_words_j[i], 10);
				return true;
			}
		}
		break;

	case 'k':
		for(int i=0; i<sizeof(slip39_words_k)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_k[i][0]) && (word_to_predict[1] == slip39_words_k[i][1]) && (word_to_predict[2] == slip39_words_k[i][2]) && (word_to_predict[3] == slip39_words_k[i][3])){
				memcpy(word_to_predict, slip39_words_k[i], 10);
				return true;
			}
		}
		break;

	case 'l':
		for(int i=0; i<sizeof(slip39_words_l)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_l[i][0]) && (word_to_predict[1] == slip39_words_l[i][1]) && (word_to_predict[2] == slip39_words_l[i][2]) && (word_to_predict[3] == slip39_words_l[i][3])){
				memcpy(word_to_predict, slip39_words_l[i], 10);
				return true;
			}
		}
		break;

	case 'm':
		for(int i=0; i<sizeof(slip39_words_m)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_m[i][0]) && (word_to_predict[1] == slip39_words_m[i][1]) && (word_to_predict[2] == slip39_words_m[i][2]) && (word_to_predict[3] == slip39_words_m[i][3])){
				memcpy(word_to_predict, slip39_words_m[i], 10);
				return true;
			}
		}
		break;

	case 'n':
		for(int i=0; i<sizeof(slip39_words_n)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_n[i][0]) && (word_to_predict[1] == slip39_words_n[i][1]) && (word_to_predict[2] == slip39_words_n[i][2]) && (word_to_predict[3] == slip39_words_n[i][3])){
				memcpy(word_to_predict, slip39_words_n[i], 10);
				return true;
			}
		}
		break;

	case 'o':
		for(int i=0; i<sizeof(slip39_words_o)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_o[i][0]) && (word_to_predict[1] == slip39_words_o[i][1]) && (word_to_predict[2] == slip39_words_o[i][2]) && (word_to_predict[3] == slip39_words_o[i][3])){
				memcpy(word_to_predict, slip39_words_o[i], 10);
				return true;
			}
		}
		break;

	case 'p':
		for(int i=0; i<sizeof(slip39_words_p)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_p[i][0]) && (word_to_predict[1] == slip39_words_p[i][1]) && (word_to_predict[2] == slip39_words_p[i][2]) && (word_to_predict[3] == slip39_words_p[i][3])){
				memcpy(word_to_predict, slip39_words_p[i], 10);
				return true;
			}
		}
		break;

	case 'q':
		for(int i=0; i<sizeof(slip39_words_q)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_q[i][0]) && (word_to_predict[1] == slip39_words_q[i][1]) && (word_to_predict[2] == slip39_words_q[i][2]) && (word_to_predict[3] == slip39_words_q[i][3])){
				memcpy(word_to_predict, slip39_words_q[i], 10);
				return true;
			}
		}
		break;

	case 'r':
		for(int i=0; i<sizeof(slip39_words_r)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_r[i][0]) && (word_to_predict[1] == slip39_words_r[i][1]) && (word_to_predict[2] == slip39_words_r[i][2]) && (word_to_predict[3] == slip39_words_r[i][3])){
				memcpy(word_to_predict, slip39_words_r[i], 10);
				return true;
			}
		}
		break;

	case 's':
		for(int i=0; i<sizeof(slip39_words_s)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_s[i][0]) && (word_to_predict[1] == slip39_words_s[i][1]) && (word_to_predict[2] == slip39_words_s[i][2]) && (word_to_predict[3] == slip39_words_s[i][3])){
				memcpy(word_to_predict, slip39_words_s[i], 10);
				return true;
			}
		}
		break;

	case 't':
		for(int i=0; i<sizeof(slip39_words_t)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_t[i][0]) && (word_to_predict[1] == slip39_words_t[i][1]) && (word_to_predict[2] == slip39_words_t[i][2]) && (word_to_predict[3] == slip39_words_t[i][3])){
				memcpy(word_to_predict, slip39_words_t[i], 10);
				return true;
			}
		}
		break;

	case 'u':
		for(int i=0; i<sizeof(slip39_words_u)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_u[i][0]) && (word_to_predict[1] == slip39_words_u[i][1]) && (word_to_predict[2] == slip39_words_u[i][2]) && (word_to_predict[3] == slip39_words_u[i][3])){
				memcpy(word_to_predict, slip39_words_u[i], 10);
				return true;
			}
		}
		break;

	case 'v':
		for(int i=0; i<sizeof(slip39_words_v)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_v[i][0]) && (word_to_predict[1] == slip39_words_v[i][1]) && (word_to_predict[2] == slip39_words_v[i][2]) && (word_to_predict[3] == slip39_words_v[i][3])){
				memcpy(word_to_predict, slip39_words_v[i], 10);
				return true;
			}
		}
		break;

	case 'w':
		for(int i=0; i<sizeof(slip39_words_w)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_w[i][0]) && (word_to_predict[1] == slip39_words_w[i][1]) && (word_to_predict[2] == slip39_words_w[i][2]) && (word_to_predict[3] == slip39_words_w[i][3])){
				memcpy(word_to_predict, slip39_words_w[i], 10);
				return true;
			}
		}
		break;

	case 'y':
		for(int i=0; i<sizeof(slip39_words_y)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_y[i][0]) && (word_to_predict[1] == slip39_words_y[i][1]) && (word_to_predict[2] == slip39_words_y[i][2]) && (word_to_predict[3] == slip39_words_y[i][3])){
				memcpy(word_to_predict, slip39_words_y[i], 10);
				return true;
			}
		}
		break;

	case 'z':
		for(int i=0; i<sizeof(slip39_words_z)/10; i++)
		{
			if((word_to_predict[0] == slip39_words_z[i][0]) && (word_to_predict[1] == slip39_words_z[i][1]) && (word_to_predict[2] == slip39_words_z[i][2]) && (word_to_predict[3] == slip39_words_z[i][3])){
				memcpy(word_to_predict, slip39_words_z[i], 10);
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




