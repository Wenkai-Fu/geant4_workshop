#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	// internal material database
	G4NistManager* nist = G4NistManager::Instance();
	G4Material* air = nist -> FindOrBuildMaterial("G4_AIR");
	G4Material* wax = nist -> FindOrBuildMaterial("G4_PARAFFIN");


	G4double boxx = 10.0 * cm, boxy = 10.0 * cm, boxz = 10.0 * cm;

	// world
	G4Box* world_solid = new G4Box("world_solid",
			boxx,  // half length
			boxy,
			boxz);

	G4LogicalVolume* world_lv = new G4LogicalVolume(world_solid,
			air,
			"world_lv");

	G4VPhysicalVolume* world_pv = new G4PVPlacement(0,  // rotation matrix
			G4ThreeVector(),                            // translation vector
			world_lv,                                   // lv
			"world_pv",                                 // pv name
			0,                                          // mother lv
			false,                                      // future use
			0,                                          // copy number
			true);                                      // surface check

	// tank
    G4Box* tank_solid = new G4Box("tank_box",
    		boxx * 0.5,
			boxy * 0.5,
			boxz * 0.5);

    G4LogicalVolume* tank_lv = new G4LogicalVolume(tank_solid, wax, "tank_lv");

    G4VPhysicalVolume* tank_pv = new G4PVPlacement(0,  // rotation matrix
			G4ThreeVector(),                            // translation vector
			tank_lv,                                   // lv
			"tank_pv",                                 // pv name
			world_lv,                                   // mother lv
			false,                                      // future use
			0,                                          // copy number
			true);                                      // surface check

	return world_pv;
}
