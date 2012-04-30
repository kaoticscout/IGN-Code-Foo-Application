#ifndef GAMEPIECE_H
#define GAMEPIECE_H

enum PLAYERTYPE
{
	NONE,
	PLAYERONE,
	PLAYERTWO,
	TIE
};

class Gamepiece
{
public:
	Gamepiece(PLAYERTYPE owner) 
		: m_Owner(owner)
	{}

	PLAYERTYPE GetOwner() { return m_Owner; }
	void SetOwner(PLAYERTYPE type) { m_Owner = type; }

private:
	PLAYERTYPE m_Owner;

};

#endif