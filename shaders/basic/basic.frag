#version 460 core

in vec3 position;
in vec3 normal;

out vec4 fragColor;

struct Light {
    vec3 position;
    float strength; // light strength affects diffuse and specular light intensity

    float diffuse_coefficient;
    vec3 diffuse_color;

    float specular_coefficient;
    vec3 specular_color;

    float ambient_coefficient;
    vec3 ambient_color;
};

uniform vec3 camera_pos;

uniform vec3 color;
uniform unsigned int shininess;

uniform Light light;


void main() {
    vec3 normal_ = normalize(normal);
    vec3 light_dir = normalize(light.position - position);
    // Diffuse factor depending on the angle between normal vector and light direction
    float diff = light.strength * light.diffuse_coefficient * max(dot(normal_, light_dir), 0.f);
    vec3 diffuse = diff * light.diffuse_color;

    vec3 view_dir = normalize(camera_pos - position);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    // Specular factor depending on the angle between view direction and reflection
    float spec = light.strength * light.specular_coefficient * pow(max(dot(normal_, halfway_dir), 0.f), shininess);
    vec3 specular = spec * light.specular_color;

    // Squared distance between light position and fragment position
    float dist_squared = dot(light.position - position, light.position - position);
    // Attenuation
    diffuse /= dist_squared;
    specular /= dist_squared;

    vec3 ambient = light.ambient_coefficient * light.ambient_color;

    fragColor = vec4(color * (ambient + diffuse + specular), 1.f);
}
