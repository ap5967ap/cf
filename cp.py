import json
import os

def create_files_from_snippets(snippet_path, output_dir):
    
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
        print(f"Created directory: '{output_dir}'")

    try:
        
        with open(snippet_path, 'r', encoding='utf-8') as f:
            snippets_data = json.load(f)

        
        for key, value in snippets_data.items():
            print(key)
            
            if key.startswith('template_'):
                base_name = key[len('template_'):]
            else:
                base_name = key
            
            output_filename = f"{base_name}.cpp"
            output_filepath = os.path.join(output_dir, output_filename)

            
            if 'body' in value and isinstance(value['body'], list):
                
                code_content = '\n'.join(value['body'])

                
                with open(output_filepath, 'w', encoding='utf-8') as out_file:
                    out_file.write(code_content)
                
                print(f"Successfully created: {output_filepath}")
            else:
                print(f"Warning: Skipping '{key}' because its 'body' is missing or not a list.")

    except FileNotFoundError:
        print(f"Error: The file '{snippet_path}' was not found.")
    except json.JSONDecodeError:
        print(f"Error: Could not decode JSON from '{snippet_path}'. Make sure it's a valid JSON file.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

if __name__ == '__main__':
    
    SNIPPET_FILE = '/home/ap/cf/.vscode/snippets.code-snippets'
    OUTPUT_DIRECTORY = 'ap'
    
    
    create_files_from_snippets(SNIPPET_FILE, OUTPUT_DIRECTORY)
