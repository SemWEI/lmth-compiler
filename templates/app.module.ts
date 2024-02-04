import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppComponent } from './app.component';
${IMPORT_COMPONENTS}

@NgModule({
  declarations: [
    AppComponent,
    ${DECLARATIONS}
  ],
  imports: [
    BrowserModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }