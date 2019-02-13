#include "RunAction.hh"

RunAction::RunAction()
: G4UserRunAction(),
  rerg(0.0),
  rerg2(0.0)
{
	// register accumulable
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager -> RegisterAccumulable(rerg);
	accumulableManager -> RegisterAccumulable(rerg2);
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* run)
{}

void RunAction::EndOfRunAction(const G4Run* run)
{
	// merge accumulables
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager -> Merge();

	// get value
	G4double verg = rerg.GetValue();
	G4double verg2 = rerg2.GetValue();

	// Print
	if (IsMaster()) {
		G4cout << G4endl
	    << "--------------------End of Global Run-----------------------\n";

		G4int nofEvents = run -> GetNumberOfEvent();
		vec_double ans = cal_ave(verg, verg2, nofEvents);
		G4cout << "Ave. total deposited energy in tank, relative error = "
		<< ans[0] / MeV << " MeV,  " << ans[1] << G4endl;
	}
}

vec_double RunAction::cal_ave(G4double var, G4double var2, G4int n){
	/*
	 * Compute average value and relative error.
	 * Parameters:
	 *      var: sum of tally
	 *     var2: sum of tally^2
	 *        n: number of histories
	 *
	 * Return: a size-two vector with
	 *               ans[0] = average value
	 *               ans[1] = relative error
	 */
	vec_double ans(2);
	G4double ave = var / n, ave2 = var2 / n;
	ans[0] = ave;
	G4double std_dev = sqrt((ave2 - ave * ave) / (n - 1));
	if (fabs(ave) < 1.0e-20)
		// if no tally, set the relative error to 1
		ans[1] = 1.0;
	else
		ans[1] = std_dev / ave;
	return ans;
}

void RunAction::Accumulate_event(G4double eerg){
	rerg += eerg;
	rerg2 += eerg * eerg;
}
