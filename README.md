# Graphics Final Project
### Name: Ayan Chowdhury
### Class Period: 4
---
## New Graphics Engine Features
  - Lighting 
    - Allow for multiple point lights
    - Add point lights and set ambient light via mdl
  - Shading
    - Phong Shading
    - Gouraud  Shading 
  - Opacity (maybe)
    - Not sure about this but want to try to make 3d objects that are transparent  
  - Read external images (maybe)
    - Script that converts vector files and .obj files into mdl    
---
## The Details
Completed:
  - Lighting
    - Can use multiple point lights within an mdl file
  - Shading
    - Gouraud Shading
      - Works, but has some weird artifacts
    - Phong Shading
      - Works and doesn't have as many weird artifacts as Gouraud
  - Read external images
    - Did not implement mesh, but have a python script that can turn .obj into code that uses my engine (did not implement it with mdl) and used it for the teapot and diamond