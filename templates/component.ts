import { Component, OnInit } from '@angular/core';
import { ${SERVICE_NAME} } from '../services/${SERVICE_NAME}.service';
import { ${MODEL_NAME} } from '../models/${MODEL_NAME}';

@Component({
  selector: '${selector}',
  templateUrl: '${templateUrl}',
  styleUrls: ['${styleUrl}']
})
export class ${name}Component implements OnInit {
  ${MODEL_NAME_LOWER}List: ${MODEL_NAME}[];

  constructor(private ${SERVICE_NAME_LOWER}: ${SERVICE_NAME}) {}

  ngOnInit(): void {
    this.${SERVICE_NAME_LOWER}.${METHOD_NAME}().subscribe(data => {
      this.${MODEL_NAME_LOWER}List = data;
    });
  }
}