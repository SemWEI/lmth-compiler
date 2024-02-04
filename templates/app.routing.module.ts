import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
${IMPORT_COMPONENTS}

const routes: Routes = [
  ${ROUTES}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }