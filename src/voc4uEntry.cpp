/**
 * This file contains the bada application entry point.
 */
#include "voc4u.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

_EXPORT_ int OspMain(int argc, char *pArgv[]);

/**
 *
 * vote
obsession
struck
particularly
consideration
nested
on store
amplifies
ponder
whether
tutor
According
admissions
applicants
decline
moron
additionaly
harked
credited
enthusiasts
fraction
hence
prompt
sounded
spurred
flurry
governmental
ripe
alignment
once
pugnacious
hurdle
advantage
vibrant
amount
led
awesome
widespread
delight
contributions
survey
further
satisfy
achieve
payback
mandatory
purpose
forth
statement
bind
poverty
nutritious
affordable
grassroots
self-reliance
empowerment
outlook
deteriorated
attract talent
trickier
beyond
negotiating
considering
hiring
nowadays
verify
maintenance
assuming
rather
tethered
pivotal
unease
unsurprisingly
resilience
unconventional
stomping
decades
sand
punctuation
profanity
silence
profound
boom
shale
pronunciation
leak
cattle
scarcer
scorching
yearlong drought
thick
clutches
pull
stare
vessel
fledgling
apparently
occured

hlas
posedlost
udeřil
zvláště
pozornost
vnořené
skladem
zesílí
uvažovat
zda
vychovatel
podle
Přijímací řízení
žadatele
pokles
kretén
dodatečně
naslouchali
připsány
nadšence
zlomek
proto
řádku
znělo
pobídl
rozruch
vládní
zralý
sladění
jednou
útočný
překážka
výhoda
živý
množství
vedl
děsivý
rozšířený
radost
příspěvky
průzkum
dále
uspokojit
dosáhnout
návratnosti
povinné
účel
dále
tvrzení
vázat
chudoba
výživný
dostupné
nejnižší
soběstačnost
zmocnění
výhled
zhoršila
přilákat talenty
složitější
za
jednání
s ohledem na
pronájem
nyní
ověřit
údržba
za předpokladu, že
spíše
upoutané
rozhodující
neklid
Není překvapením
pružnost
nekonvenční
stomping
desetiletí
písek
interpunkce
neuctivost
mlčení
hluboký
výložník
břidlice
výslovnost
únik
dobytek
vzácnější
sálající
roční období sucha
tlustý
spárů
táhnout
pohledem
plavidlo
fledgling
zřejmě
došlo
 * The entry function of bada application called by the operating system.
 */
int
OspMain(int argc, char *pArgv[]){
	result r = E_SUCCESS;

	AppLog("Application started.");
	ArrayList* pArgs = new ArrayList();
	pArgs->Construct();
	for (int i = 0; i < argc; i++)
		pArgs->Add(*(new String(pArgv[i])));

	r = Osp::App::Application::Execute(voc4u::CreateInstance, pArgs);
	if (IsFailed(r))
	{
		AppLogException("Application execution failed-[%s].", GetErrorMessage(r));
		r &= 0x0000FFFF;
	}

	pArgs->RemoveAll(true);
	delete pArgs;
	AppLog("Application finished.");

	return static_cast<int>(r);
}
#ifdef __cplusplus
}
#endif // __cplusplus
