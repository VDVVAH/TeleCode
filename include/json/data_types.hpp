class Json {
public:
    Json(JsonNode& root);
};

// TODO: magic of metaprogramming as template for casting from void* propability on enum.

class JsonNode {
private:
    void* value;
    const JsonNode* childs;
    JsonNode& parent;

public:    
    JsonNode(JsonNode[]);
    JsonNode(JsonNode&);
    JsonNode(JsonNode&&);
    JsonNode& operator=(JsonNode&);
    JsonNode& operator=(JsonNode&&);
    ~JsonNode();

    virtual void* getValue();
    JsonNode* getChilds();
    JsonNode& getParent();
    virtual bool isLeaf();
    virtual bool isRoot();
};

class JsonRoot: public JsonNode {

}