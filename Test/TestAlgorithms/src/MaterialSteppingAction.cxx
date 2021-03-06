//
//  MaterialSteppingAction.cxx
//
//
//  Created by Julia Hrdinka on 18/05/15.
//
//

#include "TestAlgorithms/MaterialSteppingAction.h"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include <G4VSensitiveDetector.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialSteppingAction* MaterialSteppingAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialSteppingAction* MaterialSteppingAction::Instance()
{
    // Static acces function via G4RunManager

    return fgInstance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialSteppingAction::MaterialSteppingAction()
: G4UserSteppingAction(),
m_tInX0(0.),
m_pathlength(0.),
m_counter(0)
{
    fgInstance = this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialSteppingAction::~MaterialSteppingAction()
{
    fgInstance = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MaterialSteppingAction::UserSteppingAction(const G4Step* step)
{
    // get volume of the current step
    G4String material = step->GetPreStepPoint()->GetTouchableHandle()
    ->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName();
    G4double steplength = step->GetStepLength();
    if (material!="Air" && material!="Vacuum") {
       // steplength = step->GetStepLength();
        G4double radlength  = step->GetPreStepPoint()->GetTouchableHandle()
        ->GetVolume()->GetLogicalVolume()->GetMaterial()->GetRadlen();
        // m_tInX0 = radlength;
        m_tInX0 += steplength/radlength;
        // steplength = steplength/cm;
        m_pathlength += steplength;

    }
    G4VSensitiveDetector* sensdet= step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetSensitiveDetector();
    if (sensdet) {
        m_hits++;
        m_pos.push_back(step->GetPreStepPoint()->GetPosition());
    }

    G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MaterialSteppingAction::Reset()
{
    m_tInX0         = 0.;
    m_pathlength    = 0.;
    m_counter       = 0;
    m_hits          = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


