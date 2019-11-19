#define GET(T,member) const T& Get##member() const { return member; }
#define SET(T, member) void Set##member(const T & value) { member =value; }
#define GETSET(T, member) const T& Get##member() const { return member; } void Set##member(const T & value) { member =value; }

template<class T>
void const SAFE_DELETE(T* x) { delete x; x = nullptr; }

template<class T>
void const SAFE_RELEASE(T* x) { x->Release(); x = nullptr; }

#define GAMEOBJECT() public : virtual void Update(float frameTime); virtual void Render(float frameTime);
