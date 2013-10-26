#include <stdio.h>
#include <string.h>
#include "file.h"


char filename[MAX_PATH_LENGHT] = "s:\\sources\\meixian\\dazi\\Release\\file\\python.txt";
char word[MAX_WORD_COUNT][MAX_WORD_LENGHT]={
"pen", "pencil", "pencil", "ruler", "eraser", "crayon", "book", "bag", "school", 
"sharpener", "hello", "hi", "my", "name", "goodbay", "bye", "what", 
"is", "your", "you", "head", "face", "nose", "mouth", "eye", 
"ear", "arm", "hand", "finger", "leg", "foot", "food", "body", 
"good", "morning", "this", "nice", "meet", "go", "to", "afternoon", 
"too", "red", "yellow", "green", "blue", "purple", "white", "black", 
"orange", "pink", "brown", "how", "are", "fine", "thank", "thanks", 
"paint", "great", "cat", "dog", "monkey", "panda", "rabbit", "duck", 
"pig", "birdb", "bear", "mouse", "elephant", "squirrel", "have", "super", 
"zoo", "really", "may", "sure", "like", "it", "cake", "bread", 
"hot", "hamburger", "chicken", "French", "French", "Coke", "cock", "juice", 
"milk", "water", "tea", "coffee", "some", "and", "no", "can", 
"one", "two", "three", "four", "five", "six", "seven", "eight", 
"nine", "ten", "doll", "boat", "ship", "ball", "kite", "balloon", 
"car", "plane", "friend", "for", "happy", "birthday", "how", "eat", 
"how", "how", "gift", "boy", "girl", "teacher", "student", "this", 
"my", "friend", "nice", "meet", "welcome", "back", "new", "where", 
"you", "your", "America", "see", "say", "again", "class", "we", 
"today", "watchout", "sorry", "ant", "apple", "Come", "egg", "father", 
"dad", "mother", "mom", "man", "woman", "grandmother", "grandma", "grandfather", 
"grandpa", "sister", "brother", "great", "really", "and", "how", "family", 
"come", "who", "that", "she", "he", "fish", "funny", "fun", 
"watch", "TV", "watch", "big", "ice", "ice", "eleven", "twelve", 
"thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty", 
"can", "look", "fly", "draw", "picture", "beautiful", "jeep", "jump", 
"kangaroo", "key", "guess", "open", "right", "lion", "lock", "night", 
"nest", "peach", "orange", "apple", "banana", "strawberry", "grape", "like", 
"hungry", "please", "them", "very", "taste", "queen", "quiet", "fruit", 
"certainly", "rainbow", "rain", "snake", "tiger", "taxi", "bus", "bike", 
"desk", "chair", "walkman", "lamp", "play", "game", "here", "toy", 
"box", "Under", "On", "umbrella", "look", "violin", "vest", "window", 
"wind", "excuse", "no", "here", "zebra", "use", "us", "yo", 
"small", "big", "long", "short", "tall", "giraffe", "deer", "dear", 
"cute", "lovely", "at", "feed", "animal", "children", "so", "has", 
"tail", "CAN", "PRC", "UK", "USA", "M", "P", "board", 
"light", "picture", "door", "floor", "classroom", "many", "our", "classmate", 
"have", "seat", "near", "new", "where", "computer", "teacher", "wall", 
"fan", "clean", "good", "all", "good", "Chinese", "English", "math", 
"schoolbag", "story", "notebook", "colour", "fat", "may", "sure", "here", 
"twenty", "thirty", "thirty", "forty", "forty", "fifty", "too", "heavy", 
"sorry", "long", "short", "thin", "strong", "quiet", "friend", "Chinese", 
"photo", "music", "science", "sports", "painting", "computer", "her", "right", 
"study", "bathroom", "bedroom", "living", "kitchen", "fish", "room", "open", 
"close", "phone", "sofa", "shelf", "fridge", "rice", "noodle", "soup", 
"vegetable", "beef", "dinner", "wait", "hungry", "knife", "chopstick", "spoon", 
"plate", "plane", "fork", "pass", "ready", "try", "helpyourself", "show", 
"yummy", "use", "family", "parents", "uncle", "aunt", "baby", "people", 
"member", "only", "puppy", "baseball", "driver", "doctor", "farm", "farmer", 
"nurse", "garden", "teacher", "library", "canteen", "first", "visitor", "there", 
"lunch", "this", "that", "art", "computer", "washroom", "music", "gym", 
"TV", "second", "cool", "English", "music", "breakfast", "P", "over", 
"go", "just", "go", "kid", "run", "get", "go", "go", 
"ready", "hurry", "math", "Chinese", "china", "England", "English", "P", 
"class", "music", "for", "jacket", "shirt", "T", "skirt", "dress", 
"sweater", "whose", "no", "not", "jeans", "pants", "parents", "socks", 
"shoes", "shorts", "these", "those", "what", "neighbour", "colour", "warm", 
"cold", "cool", "hot", "weather", "weather", "wear", "football", "put", 
"wear", "rain", "rainy", "now", "snow", "snowy", "wind", "windy", 
"cloud", "cloudy", "sun", "sunny", "not", "New", "matter", "have", 
"colourful", "pretty", "cheap", "expensive", "sixty", "seventy", "hundred", "how", 
"ninety", "sneakers", "slippers", "sandals", "boots", "want", "pair", "a", 
"son", "sun", "size", "take", "them", "sheep", "horse", "hen", 
"lamb", "goat", "cow", "donkey", "key", "rabbit", "pig", "duck", 
"tomoto", "cucumber", "potato", "onion", "carrot", "fresh", "there", "young", 
"funny", "tall", "strong", "kind", "old", "who", "Mr", "from", 
"Canada", "what", "like", "know", "now", "no", "principal", "university", 
"strict", "Miss", "smart", "active", "Lady", "so", "fun", "quiet", 
"she", "he", "her", "his", "very", "but", "Monday", "Tuesday", 
"Wednesday", "Thursday", "Friday", "Moral", "day", "Social", "wait", "waiter", 
"tomorrow", "have", "on", "do", "watch", "read", "Saturday", "Sunday", 
"sometimes", "usually", "love", "what", "yeah", "play", "too", "to", 
"do", "cabbage", "pork", "mutton", "eggplant", "egg", "plant", "tofu", 
"fish", "green", "potato", "tomato", "for", "lunch", "we", "menu", 
"sound", "healthy", "tasty", "sweet", "adj", "sour", "fresh", "salty", 
"they", "favourite", "fruit", "grape", "have", "eat", "empty", "cook", 
"water", "sweep", "clean", "ill", "helpful", "at", "wash", "just", 
"do", "make", "robot", "set", "wash", "do", "put", "I", 
"would", "have", "play", "use", "air", "curtain", "trash", "closet", 
"close", "mirror", "end", "look", "own", "flat", "third", "bedroom", 
"kitchen", "bathroom", "living", "very", "in", "on", "under", "near", 
"behind", "over", "in", "clothes", "work", "tell", "cloud", "mountain", 
"river", "flower", "grass", "lake", "forest", "path", "park", "nature", 
"farm", "farmer", "holiday", "picture", "village", "city", "house", "bridge", 
"tree", "road", "building", "clean", "air", "run", "any", "do", 
"eat", "have", "play", "eat", "when", "about", "policeman", "work", 
"evening", "get", "at", "usually", "noon", "tell", "climbing", "go", 
"play", "visit", "go", "weekend", "week", "end", "often", "sometimes", 
"rain", "either", "next", "spring", "summer", "fall", "winter", "season", 
"which", "best", "always", "play", "snow", "leaf", "up", "north", 
"Halloween", "Thanksgiving", "Swim", "Fly", "skate", "make", "plant", "why", 
"because", "sleep", "January", "February", "March", "April", "May", "June", 
"July", "August", "September", "October", "November", "December", "chart", "birthday", 
"uncle", "first", "second", "third", "fourth", "fifth", "eighth", "ninth", 
"twelfth", "twentieth", "send", "e", "her", "able", "everyone", "then", 
"date", "draw", "cook", "read", "answer", "talk", "mom", "Children", 
"see", "listen", "clean", "write", "write", "grandpa", "speak", "study", 
"fly", "jump", "walk", "run", "swim", "kangaroo", "truck", "sleep", 
"climb", "fight", "swing", "drink", "climber", "take", "watch", "pick", 
"do", "ant", "catch", "woods", "interesting", "have", "honey", "thing", 
"count", "collect", "write", "play", "have", "him", "leave", "us", 
"over", "by", "fifth", "right", "china", "English", "England", "Australia", 
"left", "hospital", "cinema", "bookstore", "science", "museum", "excuse", "where", 
"please", "next", "far", "supermarket", "bank", "after", "Want", "a", 
"shoe", "get", "minute", "north", "south", "east", "west", "turn", 
"right", "left", "straight", "then", "twelfth", "party", "tell", "start", 
"take", "look", "next", "this", "This", "This", "Tonight", "tomorrow", 
"take", "read", "Go", "theme", "the", "busy", "together", "comic", 
"Post", "newspaper", "magazine", "dictionary", "shoe", "buy", "fruit", "pet", 
"need", "plant", "else", "shop", "hobby", "ride", "riding", "dive", 
"diving", "play", "make", "making", "collect", "collecting", "Show", "pen", 
"dear", "twin", "look", "something", "must", "fun", "with", "TV", 
"live", "lives", "lives", "teach", "teaches", "go", "goes", "watch", 
"watches", "read", "reades", "does", "doesn", "different", "week", "say", 
"soon", "excited", "sing", "singer", "Write", "Writer", "Work", "Worker", 
"farm", "farmer", "teach", "teacher", "actor", "actress", "artist", "TV", 
"Show", "n", "Hong", "engineer", "accountant", "police", "policeman", "policewoman", 
"salesperson", "clean", "cleaner", "company", "where", "factory", "design", "tip", 
"help", "money", "enjoy", "tourist", "way", "motor", "rain", "cloud", 
"vapour", "sun", "stream", "come", "shine", "become", "little", "drop", 
"wake", "feel", "think", "meet", "high", "other", "fall", "dwon", 
"into", "come", "again", "seed", "Soil", "Sprout", "Plant", "Should", 
"then", "garden", "easy", "put", "several", "day", "see", "pot", 
"lovely", "make", "get", "get", "month", "old", "still", "hardly", 
"come", "taller", "shorter", "stronger", "older", "younger", "cm", "than", 
"little", "tail", "think", "fun", "funny", "funnier", "kg"
};
int total_word = MAX_WORD_COUNT;

//读取文件初始化单词表
int setFile()
{
	FILE *fp;
	int i;
	char str[MAX_WORD_LENGHT];
	
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return -1;
	}

	for(i=0;(fscanf(fp, "%s", str)) != EOF;i++) {
		if (i>=MAX_WORD_COUNT)
		{
			break;
		}
		strcpy(word[i], str);
	}
	total_word = i;
	fclose(fp);
	return 0;
}
//设置单词文件的名字
int setFilename(char *path)
{
	strcpy(filename, path);
	return setFile();
}