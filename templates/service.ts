import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { ${MODEL_NAME} } from '../models/${MODEL_NAME}';

@Injectable({
  providedIn: 'root'
})
export class ${name}Service {
  constructor(private http: HttpClient) {}

  ${METHOD_IMPLEMENTATIONS}
}
