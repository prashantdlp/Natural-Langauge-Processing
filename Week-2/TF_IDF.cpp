#include<unordered_set>
#include<unordered_map>
#include<iostream>
#include<vector>
#include<string>
#include<cmath>

const std::unordered_set<std::string> STOP_WORDS = {
    "a","an","and","are","as","at","be","by","for","from","has","he",
    "in","is","it","its","of","on","that","the","to","was","were","will","with"
};

std::vector<std::string>corpus= {
    "Amazing movie with a great story",
    "Loved the performances and direction",
    "A wonderful cinematic experience",
    "Brilliant acting and beautiful visuals",
    "An inspiring and emotional film",
    "Great screenplay and strong characters",
    "One of the best movies I have seen",
    "Excellent plot and execution",
    "A masterpiece worth watching",
    "Very engaging and entertaining",
    "Fantastic storytelling throughout",
    "Heartwarming and well made",
    "Superb music and cinematography",
    "A delightful and enjoyable film",
    "Powerful performances by the cast",
    "An outstanding and memorable movie",
    "Loved every minute of it",
    "A highly recommended film",
    "Great balance of emotion and drama",
    "An exceptional movie experience",
    "The movie was truly impressive",
    "Strong story with great direction",
    "Amazing visuals and sound design",
    "A beautifully crafted film",
    "The plot was engaging and smart",
    "Excellent acting by all actors",
    "A very satisfying movie",
    "One of my favorite movies",
    "The film exceeded expectations",
    "An emotionally rich movie",
    "Top-notch production quality",
    "The movie was fantastic",
    "Great pacing and storyline",
    "An enjoyable watch from start to end",
    "Very well executed film",
    "The acting was brilliant",
    "A compelling and touching story",
    "An entertaining and meaningful movie",
    "The direction was outstanding",
    "A truly enjoyable film",
    "Loved the story and characters",
    "The movie was refreshing",
    "A solid and well-made film",
    "An impressive piece of cinema",
    "Highly enjoyable movie",
    "A great movie overall",
    "The film was excellent",
    "Wonderful performances",
    "A must-watch movie",
    "Simply amazing film"
};

std::vector<std::string>tokenize(const std::string& str){
    std::vector<std::string>tokens;
    std::string word;

    for (char ch : str) {
        if (isalpha(ch)) {
            word += tolower(ch);
        }else {
            if (!word.empty() && !STOP_WORDS.count(word)) {
                tokens.push_back(word);
            }
            word.clear();
        }
    }

    if (!word.empty() && !STOP_WORDS.count(word)) {
        tokens.push_back(word);
    }

    return tokens;
}

int main(){
    int n = corpus.size();
    std::vector<std::unordered_map<std::string,double>>TF(n);
    std::unordered_map<std::string,std::vector<int>>page_existence;
    
    for (int i = 0; i < n; i++) {
        auto tokens = tokenize(corpus[i]);
        int m = tokens.size();
        if (m == 0) continue;

        for (const auto& t : tokens) {
            TF[i][t] += 1.0 / m;

            auto& pages = page_existence[t];
            if (pages.empty() || pages.back() != i) {
                pages.push_back(i);
            }
        }
    }
    
    std::unordered_map<std::string,double>IDF;
    for (const auto& [token, pages] : page_existence) {
        IDF[token] = log((double)n / pages.size());
    }

    auto TF_IDF = [&](int episode, const std::string& token) -> double {
        if (episode < 0 || episode >= n){
            return 0.0f;
        }

        auto tf_it = TF[episode].find(token);
        auto idf_it = IDF.find(token);

        if (tf_it == TF[episode].end() || idf_it == IDF.end()){
            return 0.0f;
        }

        return tf_it->second * idf_it->second;
    };

    int episode;
    std::string token;

    std::cout << "episode: ";
    std::cin >> episode;
    std::cout << "token: ";
    std::cin >> token;

    std::cout << TF_IDF(episode, token) << "\n";
 
    return 0;
}