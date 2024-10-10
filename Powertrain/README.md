University of Windsor Formula Student Electric Powertrain Team
Welcome to the Git repository for the University of Windsor Formula Student Electric Powertrain Team. This repository serves as the central location for managing and organizing all aspects of our electric powertrain design and development, including:

PCB designs
Wire harness diagrams
Motor and drivetrain calculations
Design revisions and documentation
Repository Structure
The repository is organized into the following directories:

PCB Designs
Contains all printed circuit board (PCB) designs for the powertrain's electronic systems, including motor controllers, battery management systems (BMS), and sensor interfaces. Each design includes:

Schematic files
Layout files
Bill of Materials (BOM)
Fabrication outputs (Gerber files, pick-and-place data)
Ensure all revisions are clearly labeled by version number (e.g., v1.0, v1.1) and documented in the respective README or changelog within this directory.

Wire Harnesses
This section holds the wiring diagrams for the vehicle's electrical systems, including motor connections, sensor interfaces, and battery systems. Files may include:

Wire gauge and length specifications
Connector types
Pinouts and routing guidelines
Follow the naming convention for each version and update as necessary.

Motor Calculations
This directory stores all motor and powertrain calculations. Key calculations include:

Torque and speed curves
Efficiency plots
Electrical characteristics (voltage, current, etc.)
Ensure to include the formulas and assumptions used in the calculation process, as well as any simulation or test data.

Revisions & Documentation
Contains the log of revisions for all components, organized by subsystem (e.g., "Motor Control", "Battery Management"). For each revision, document:

The issue addressed or improvement made
Any test data validating the changes
Date of the revision and responsible team member
Use clear and consistent version control practices (e.g., Git branching) to manage updates.

Contribution Guidelines
Branching Model: Follow a feature-branch workflow. Develop new features or revisions in separate branches and submit pull requests for review before merging into the main branch.
Commit Messages: Use concise and descriptive commit messages that reflect the changes made (e.g., Added new BMS PCB schematic v2.0).
Versioning: Use semantic versioning (e.g., v1.0.0) for all major updates to PCBs, wire harnesses, and motor calculations. Minor updates or bug fixes should increment the patch number (e.g., v1.0.1).
Getting Started
Clone the repository:

bash
Copy code
git clone https://github.com/UWindsorFormulaElectric/Powertrain.git
Navigate to the desired section and review the files as needed.

Create a new branch for any updates or design revisions:

arduino
Copy code
git checkout -b feature/new-design-v1.1
Submit a pull request after making your changes.

License
This repository is for use by the University of Windsor Formula Student Electric Powertrain Team and collaborators only. All designs and calculations are proprietary and should not be distributed outside the team without permission.


